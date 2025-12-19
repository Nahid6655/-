#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <libpq-fe.h>

using namespace std;

struct Sale {
    int sale_id;
    string sale_date;
    int product_id;
    int customer_id;
    int quantity;
    double amount;
};

struct Product {
    int product_id;
    string product_name;
    string category;
    double price;
};

struct Customer {
    int customer_id;
    string customer_name;
    string region;
};

// Connect to database
PGconn* connectDB() {
    // Пробуем разные варианты подключения
    const char* connStrings[] = {
        "host=localhost port=5432 dbname=sales_dwh user=postgres password=123456",
        "host=localhost port=5432 dbname=sales_dwh user=postgres",
        "host=localhost port=5432 dbname=sales_dwh"
    };

    PGconn* conn = nullptr;

    for (const char* connStr : connStrings) {
        conn = PQconnectdb(connStr);
        if (PQstatus(conn) == CONNECTION_OK) {
            cout << "Connected using: " << connStr << endl;
            return conn;
        }
        PQfinish(conn);
    }

    cout << "All connection attempts failed!" << endl;
    return nullptr;
}

// Load sales data
vector<Sale> loadSales(string filename) {
    vector<Sale> sales;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return sales;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        Sale s;
        string temp;

        getline(ss, temp, ',');
        if (temp.empty()) continue;
        s.sale_id = stoi(temp);

        getline(ss, s.sale_date, ',');
        getline(ss, temp, ','); s.product_id = stoi(temp);
        getline(ss, temp, ','); s.customer_id = stoi(temp);
        getline(ss, temp, ','); s.quantity = stoi(temp);
        getline(ss, temp, ','); s.amount = stod(temp);

        sales.push_back(s);
    }

    file.close();
    cout << "Loaded " << sales.size() << " sales" << endl;
    return sales;
}

// Load products data
vector<Product> loadProducts(string filename) {
    vector<Product> products;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return products;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        Product p;
        string temp;

        getline(ss, temp, ','); p.product_id = stoi(temp);
        getline(ss, p.product_name, ',');
        getline(ss, p.category, ',');
        getline(ss, temp, ','); p.price = stod(temp);

        products.push_back(p);
    }

    file.close();
    cout << "Loaded " << products.size() << " products" << endl;
    return products;
}

// Load customers data
vector<Customer> loadCustomers(string filename) {
    vector<Customer> customers;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return customers;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        Customer c;
        string temp;

        getline(ss, temp, ','); c.customer_id = stoi(temp);
        getline(ss, c.customer_name, ',');
        getline(ss, c.region, ',');

        customers.push_back(c);
    }

    file.close();
    cout << "Loaded " << customers.size() << " customers" << endl;
    return customers;
}

// Convert date format
string convertDate(string date_str) {
    tm tm = {};
    stringstream ss(date_str);
    ss >> get_time(&tm, "%Y-%m-%d");

    if (ss.fail()) {
        cout << "Date conversion failed for: " << date_str << endl;
        return "";
    }

    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

// Load data to database
void loadToDB(PGconn* conn, vector<Sale>& sales, vector<Product>& products, vector<Customer>& customers) {
    // Products
    for (auto& p : products) {
        string sql = "INSERT INTO products_dim (product_id, product_name, category, price) "
            "VALUES (" + to_string(p.product_id) + ", '" +
            p.product_name + "', '" + p.category + "', " +
            to_string(p.price) + ") ON CONFLICT (product_id) DO NOTHING";

        PGresult* res = PQexec(conn, sql.c_str());
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            cout << "Error inserting product: " << PQerrorMessage(conn) << endl;
        }
        PQclear(res);
    }
    cout << "Products loaded to DB" << endl;

    // Customers
    for (auto& c : customers) {
        string sql = "INSERT INTO customers_dim (customer_id, customer_name, region) "
            "VALUES (" + to_string(c.customer_id) + ", '" +
            c.customer_name + "', '" + c.region + "') ON CONFLICT (customer_id) DO NOTHING";

        PGresult* res = PQexec(conn, sql.c_str());
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            cout << "Error inserting customer: " << PQerrorMessage(conn) << endl;
        }
        PQclear(res);
    }
    cout << "Customers loaded to DB" << endl;

    // Sales
    for (auto& s : sales) {
        string date = convertDate(s.sale_date);
        if (date.empty()) {
            cout << "Skipping sale " << s.sale_id << " due to invalid date" << endl;
            continue;
        }

        string sql = "INSERT INTO sales_fact (sale_id, sale_date, product_id, customer_id, quantity, amount) "
            "VALUES (" + to_string(s.sale_id) + ", '" + date + "', " +
            to_string(s.product_id) + ", " + to_string(s.customer_id) + ", " +
            to_string(s.quantity) + ", " + to_string(s.amount) + ") ON CONFLICT (sale_id) DO NOTHING";

        PGresult* res = PQexec(conn, sql.c_str());
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            cout << "Error inserting sale " << s.sale_id << ": " << PQerrorMessage(conn) << endl;
        }
        PQclear(res);
    }
    cout << "Sales loaded to DB" << endl;
}

// Analytical queries
void runQueries(PGconn* conn) {
    cout << "\n=== ANALYTICS REPORT ===" << endl;

    // 1. Sales by category
    cout << "\n1. SALES BY CATEGORY:" << endl;
    const char* query1 =
        "SELECT p.category, SUM(s.amount) as total_sales "
        "FROM sales_fact s "
        "JOIN products_dim p ON s.product_id = p.product_id "
        "GROUP BY p.category ORDER BY total_sales DESC";

    PGresult* res = PQexec(conn, query1);
    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
        for (int i = 0; i < PQntuples(res); i++) {
            cout << PQgetvalue(res, i, 0) << ": $" << PQgetvalue(res, i, 1) << endl;
        }
    }
    else {
        cout << "Query failed: " << PQerrorMessage(conn) << endl;
    }
    PQclear(res);

    // 2. Sales by region
    cout << "\n2. SALES BY REGION:" << endl;
    const char* query2 =
        "SELECT c.region, COUNT(*) as sales_count "
        "FROM sales_fact s "
        "JOIN customers_dim c ON s.customer_id = c.customer_id "
        "GROUP BY c.region ORDER BY sales_count DESC";

    res = PQexec(conn, query2);
    if (PQresultStatus(res) == PGRES_TUPLES_OK) {
        for (int i = 0; i < PQntuples(res); i++) {
            cout << PQgetvalue(res, i, 0) << ": " << PQgetvalue(res, i, 1) << " sales" << endl;
        }
    }
    PQclear(res);
}

// Create test CSV files
void createTestFiles() {
    // sales.csv
    ofstream sfile("sales.csv");
    sfile << "sale_id,sale_date,product_id,customer_id,quantity,amount\n";
    sfile << "1,2024-01-15,101,1,2,199.98\n";
    sfile << "2,2024-01-16,102,2,1,89.99\n";
    sfile << "3,2024-01-16,103,3,3,299.97\n";
    sfile << "4,2024-01-17,101,1,1,99.99\n";
    sfile << "5,2024-01-18,104,2,2,159.98\n";
    sfile.close();
    cout << "Created sales.csv" << endl;

    // products.csv
    ofstream pfile("products.csv");
    pfile << "product_id,product_name,category,price\n";
    pfile << "101,Laptop,Electronics,999.99\n";
    pfile << "102,Mouse,Electronics,89.99\n";
    pfile << "103,Book,Books,99.99\n";
    pfile << "104,Coffee Machine,Appliances,79.99\n";
    pfile << "105,Headphones,Electronics,149.99\n";
    pfile.close();
    cout << "Created products.csv" << endl;

    // customers.csv
    ofstream cfile("customers.csv");
    cfile << "customer_id,customer_name,region\n";
    cfile << "1,Ivan,Moscow\n";
    cfile << "2,Maria,St. Petersburg\n";
    cfile << "3,Alexey,Moscow\n";
    cfile << "4,Elena,Novosibirsk\n";
    cfile << "5,Dmitry,Kazan\n";
    cfile.close();
    cout << "Created customers.csv" << endl;
}

int main() {
    cout << "=== DWH DATA LOADER ===" << endl;

    // Create test files
    createTestFiles();

    // Connect to DB
    PGconn* conn = connectDB();
    if (!conn) {
        cout << "Cannot connect to database. Creating test files only." << endl;

        // Show what would be loaded
        cout << "\nData that would be loaded:" << endl;
        auto sales = loadSales("sales.csv");
        auto products = loadProducts("products.csv");
        auto customers = loadCustomers("customers.csv");

        return 0;
    }

    // Load data from CSV
    auto sales = loadSales("sales.csv");
    auto products = loadProducts("products.csv");
    auto customers = loadCustomers("customers.csv");

    // Load to database
    loadToDB(conn, sales, products, customers);

    // Run analytical queries
    runQueries(conn);

    // Close connection
    PQfinish(conn);
    cout << "\n=== COMPLETED SUCCESSFULLY ===" << endl;

    return 0;
}
