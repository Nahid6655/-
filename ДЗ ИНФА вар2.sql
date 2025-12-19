-- Таблица товаров
CREATE TABLE IF NOT EXISTS products_dim (
    product_id INT PRIMARY KEY,
    product_name VARCHAR(255),
    category VARCHAR(100),
    price DECIMAL(10,2)
);

-- Таблица клиентов
CREATE TABLE IF NOT EXISTS customers_dim (
    customer_id INT PRIMARY KEY,
    customer_name VARCHAR(255),
    region VARCHAR(100)
);

-- Таблица времени
CREATE TABLE IF NOT EXISTS time_dim (
    time_id SERIAL PRIMARY KEY,
    date DATE UNIQUE,
    year INT,
    quarter INT,
    month INT,
    day INT,
    day_of_week VARCHAR(20)
);

-- Таблица продаж
CREATE TABLE IF NOT EXISTS sales_fact (
    sale_id INT PRIMARY KEY,
    sale_date DATE,
    product_id INT,
    customer_id INT,
    quantity INT,
    amount DECIMAL(10,2),
    FOREIGN KEY (product_id) REFERENCES products_dim(product_id),
    FOREIGN KEY (customer_id) REFERENCES customers_dim(customer_id)
);

-- 3. Создание индексов
SELECT 'Creating indexes...' as status;

CREATE INDEX IF NOT EXISTS idx_sales_fact_product ON sales_fact(product_id);
CREATE INDEX IF NOT EXISTS idx_sales_fact_customer ON sales_fact(customer_id);
CREATE INDEX IF NOT EXISTS idx_sales_fact_date ON sales_fact(sale_date);
CREATE INDEX IF NOT EXISTS idx_products_dim_category ON products_dim(category);
CREATE INDEX IF NOT EXISTS idx_customers_dim_region ON customers_dim(region);

-- 4. Заполнение тестовыми данными
SELECT 'Inserting test data...' as status;

-- Товары
INSERT INTO products_dim (product_id, product_name, category, price) 
VALUES 
    (101, 'Laptop Dell XPS', 'Electronics', 999.99),
    (102, 'Wireless Mouse', 'Electronics', 89.99),
    (103, 'Book "C++ Programming"', 'Books', 99.99),
    (104, 'Coffee Machine', 'Appliances', 79.99),
    (105, 'Sony Headphones', 'Electronics', 149.99)
ON CONFLICT (product_id) DO UPDATE SET
    product_name = EXCLUDED.product_name,
    category = EXCLUDED.category,
    price = EXCLUDED.price;

-- Клиенты
INSERT INTO customers_dim (customer_id, customer_name, region) 
VALUES 
    (1, 'Ivan Petrov', 'Moscow'),
    (2, 'Maria Sidorova', 'St. Petersburg'),
    (3, 'Alexey Ivanov', 'Moscow'),
    (4, 'Elena Kuznetsova', 'Novosibirsk'),
    (5, 'Dmitry Smirnov', 'Kazan')
ON CONFLICT (customer_id) DO UPDATE SET
    customer_name = EXCLUDED.customer_name,
    region = EXCLUDED.region;

-- 5. Функция для заполнения дат
SELECT 'Creating time dimension function...' as status;

CREATE OR REPLACE FUNCTION populate_time_dim(start_date DATE, end_date DATE)
RETURNS void AS $$
DECLARE
    curr_date DATE := start_date;
BEGIN
    WHILE curr_date <= end_date LOOP
        INSERT INTO time_dim (date, year, quarter, month, day, day_of_week)
        VALUES (
            curr_date,
            EXTRACT(YEAR FROM curr_date),
            EXTRACT(QUARTER FROM curr_date),
            EXTRACT(MONTH FROM curr_date),
            EXTRACT(DAY FROM curr_date),
            TO_CHAR(curr_date, 'Day')
        )
        ON CONFLICT (date) DO NOTHING;
        
        curr_date := curr_date + 1;
    END LOOP;
END;
$$ LANGUAGE plpgsql;

-- 6. Заполнение дат на 2024 год
SELECT 'Populating time dimension for 2024...' as status;
SELECT populate_time_dim('2024-01-01', '2024-12-31');

-- 7. Проверка
SELECT 'DWH setup completed successfully!' as status;
SELECT 
    (SELECT COUNT(*) FROM products_dim) as products_count,
    (SELECT COUNT(*) FROM customers_dim) as customers_count,
    (SELECT COUNT(*) FROM time_dim) as dates_count,
    (SELECT COUNT(*) FROM sales_fact) as sales_count;
