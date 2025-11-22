#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Dish {
    string name;
    string type;
    double price;
};

// ------------------------------------------------------------
// Функция чтения меню из файла
// ------------------------------------------------------------
vector<Dish> readMenu(const string& filename) {
    ifstream in(filename);
    vector<Dish> dishes;
    Dish d;

    while (getline(in, d.name)) {
        getline(in, d.type);
        in >> d.price;
        in.ignore(); 
        dishes.push_back(d);
    }
    return dishes;
}

// ------------------------------------------------------------
// Функция записи меню в файл
// ------------------------------------------------------------
void writeMenu(const string& filename, const vector<Dish>& dishes) {
    ofstream out(filename);
    for (const auto& d : dishes) {
        out << d.name << "\n"
            << d.type << "\n"
            << d.price << "\n";
    }
}

// ------------------------------------------------------------
// 1. Создание файла и заполнение
// ------------------------------------------------------------
void createFile(const string& filename) {
    ofstream out(filename);

    cout << "Введите данные о блюдах. Пустая строка в названии — конец ввода.\n\n";

    while (true) {
        Dish d;

        cout << "Название блюда: ";
        getline(cin, d.name);
        if (d.name.empty()) break;

        cout << "Тип (Закуски / Основные блюда / Десерты / Напитки / Для детей): ";
        getline(cin, d.type);

        cout << "Цена блюда: ";
        cin >> d.price;
        cin.ignore();

        out << d.name << "\n" << d.type << "\n" << d.price << "\n";

        cout << "Блюдо добавлено!\n\n";
    }
    cout << "Файл успешно создан и заполнен.\n";
}

// ------------------------------------------------------------
// 2. Поиск блюда по названию
// ------------------------------------------------------------
void searchDish(const string& filename, const string& outputFile) {
    vector<Dish> dishes = readMenu(filename);
    ofstream out(outputFile, ios::app);

    string key;
    cout << "Введите название блюда: ";
    getline(cin, key);

    for (const auto& d : dishes) {
        if (d.name == key) {
            cout << "Найдено блюдо:\n";
            cout << "Название: " << d.name << "\nТип: " << d.type << "\nЦена: " << d.price << "\n";

            out << "Найдено блюдо: " << d.name << " | " << d.type << " | " << d.price << "\n";
            return;
        }
    }

    cout << "Блюдо не найдено.\n";
    out << "Блюдо не найдено: " << key << "\n";
}

// ------------------------------------------------------------
// 3. Сортировка блюда
// ------------------------------------------------------------
void sortMenu(const string& filename, const string& outputFile) {
    vector<Dish> dishes = readMenu(filename);

    int choice;
    cout << "Выберите вид сортировки:\n";
    cout << "1 — по типу\n";
    cout << "2 — по цене\n";
    cout << "Ваш выбор: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        sort(dishes.begin(), dishes.end(),
             [](const Dish& a, const Dish& b) { return a.type < b.type; });
    }
    else if (choice == 2) {
        sort(dishes.begin(), dishes.end(),
             [](const Dish& a, const Dish& b) { return a.price < b.price; });
    }
    else {
        cout << "Неверный выбор!\n";
        return;
    }

    writeMenu(filename, dishes);

    ofstream out(outputFile, ios::app);
    out << "Сортировка выполнена.\n";

    cout << "Сортировка завершена.\n";
}

// ------------------------------------------------------------
// 4. Добавление нового блюда
// ------------------------------------------------------------
void addDish(const string& filename) {
    ofstream out(filename, ios::app);
    Dish d;

    cout << "Введите название: ";
    getline(cin, d.name);

    cout << "Введите тип блюда: ";
    getline(cin, d.type);

    cout << "Введите цену: ";
    cin >> d.price;
    cin.ignore();

    out << d.name << "\n" << d.type << "\n" << d.price << "\n";

    cout << "Блюдо успешно добавлено.\n";
}

// ------------------------------------------------------------
// 5. Вывод блюд по максимальной цене
// ------------------------------------------------------------
void filterByPrice(const string& filename, const string& outputFile) {
    vector<Dish> dishes = readMenu(filename);
    double maxPrice;

    cout << "Введите максимальную цену: ";
    cin >> maxPrice;
    cin.ignore();

    ofstream out(outputFile, ios::app);

    cout << "\nБлюда с ценой ≤ " << maxPrice << ":\n";
    out << "\nБлюда с ценой ≤ " << maxPrice << ":\n";

    for (const auto& d : dishes) {
        if (d.price <= maxPrice) {
            cout << d.name << " — " << d.type << " — " << d.price << "\n";
            out << d.name << " — " << d.type << " — " << d.price << "\n";
        }
    }
}

// ------------------------------------------------------------
// 6. Вывод всего меню
// ------------------------------------------------------------
void showAllMenu(const string& filename) {
    vector<Dish> dishes = readMenu(filename);

    if (dishes.empty()) {
        cout << "Меню пусто.\n";
        return;
    }

    cout << "\n===== ВСЕ БЛЮДА МЕНЮ =====\n";
    for (const auto& d : dishes) {
        cout << "Название: " << d.name << "\n"
             << "Тип: " << d.type << "\n"
             << "Цена: " << d.price << "\n\n";
    }
}

// ------------------------------------------------------------
// Главное меню программы
// ------------------------------------------------------------
int main() {
    setlocale(LC_ALL, "Russian");

    const string menuFile = "menu.txt";
    const string outputFile = "output.txt";

    int choice;

    do {
        cout << "\n===== МЕНЮ ПРОГРАММЫ =====\n";
        cout << "1. Создать файл и заполнить\n";
        cout << "2. Найти блюдо по названию\n";
        cout << "3. Отсортировать блюда\n";
        cout << "4. Добавить блюдо\n";
        cout << "5. Вывести блюда по максимальной цене\n";
        cout << "6. Показать всё меню\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";

        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: createFile(menuFile); break;
            case 2: searchDish(menuFile, outputFile); break;
            case 3: sortMenu(menuFile, outputFile); break;
            case 4: addDish(menuFile); break;
            case 5: filterByPrice(menuFile, outputFile); break;
            case 6: showAllMenu(menuFile); break;
            case 0: cout << "Выход из программы...\n"; break;
            default: cout << "Неверный ввод! Повторите.\n";
        }

    } while (choice != 0);

    return 0;
}
