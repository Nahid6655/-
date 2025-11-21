#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

struct Dish {
    string name;
    string type;
    double price;
};

// --- Парсинг строки ---
Dish parseDish(const string& line) {
    Dish d;
    size_t p1 = line.find(';');
    size_t p2 = line.find(';', p1 + 1);

    d.name  = line.substr(0, p1);
    d.type  = line.substr(p1 + 1, p2 - p1 - 1);
    d.price = stod(line.substr(p2 + 1));
    return d;
}

// --- Преобразование блюда в строку ---
string dishToString(const Dish& d) {
    return d.name + ";" + d.type + ";" + to_string(d.price);
}

// --- Загрузка меню ---
vector<Dish> loadMenu() {
    ifstream file("menu.txt");
    vector<Dish> menu;
    string line;

    while (getline(file, line)) {
        if (!line.empty())
            menu.push_back(parseDish(line));
    }
    return menu;
}

// --- Сохранение меню ---
void saveMenu(const vector<Dish>& menu) {
    ofstream file("menu.txt");
    for (auto& d : menu)
        file << dishToString(d) << "\n";
}

// --- Лог ---
void logResult(const string& text) {
    ofstream out("output.txt", ios::app);
    out << text << "\n";
}

// === 1. Создание меню ===
void createMenuFile() {
    ofstream file("menu.txt");
    cout << "Введите блюда (пустая строка завершит ввод).\n";

    while (true) {
        Dish d;
        cout << "Название: ";
        getline(cin, d.name);
        if (d.name.empty()) break;

        cout << "Тип (Закуски, Основные блюда, Десерты, Напитки, Для детей): ";
        getline(cin, d.type);

        cout << "Цена: ";
        cin >> d.price;
        cin.ignore();

        file << dishToString(d) << "\n";
    }

    cout << "Файл menu.txt создан.\n";
    logResult("Файл menu.txt создан и заполнен.");
}

// === 2. Поиск блюда ===
void searchDish() {
    cout << "Введите название блюда: ";
    string name;
    getline(cin, name);

    vector<Dish> menu = loadMenu();
    for (auto& d : menu) {
        if (d.name == name) {
            string out = "Найдено: " + dishToString(d);
            cout << out << endl;
            logResult(out);
            return;
        }
    }

    cout << "Блюдо не найдено.\n";
    logResult("Блюдо не найдено: " + name);
}

// === 3. Сортировка ===
void sortMenu() {
    cout << "Сортировать (1 — по типу, 2 — по цене): ";
    int ch;
    cin >> ch;
    cin.ignore();

    auto menu = loadMenu();

    if (ch == 1) {
        sort(menu.begin(), menu.end(), [](auto& a, auto& b){
            return a.type < b.type;
        });
        logResult("Меню отсортировано по типу.");
    }
    else {
        sort(menu.begin(), menu.end(), [](auto& a, auto& b){
            return a.price < b.price;
        });
        logResult("Меню отсортировано по цене.");
    }

    saveMenu(menu);
    cout << "Сортировка выполнена.\n";
}

// === 4. Добавление блюда ===
void addDish() {
    Dish d;
    cout << "Название: ";
    getline(cin, d.name);

    cout << "Тип: ";
    getline(cin, d.type);

    cout << "Цена: ";
    cin >> d.price;
    cin.ignore();

    ofstream file("menu.txt", ios::app);
    file << dishToString(d) << "\n";

    cout << "Блюдо добавлено.\n";
    logResult("Добавлено: " + dishToString(d));
}

// === 5. Фильтрация по цене ===
void filterByPrice() {
    cout << "Введите максимальную цену: ";
    double maxPrice;
    cin >> maxPrice;
    cin.ignore();

    auto menu = loadMenu();

    cout << "\nБлюда с ценой <= " << maxPrice << ":\n";
    logResult("Фильтр по цене <= " + to_string(maxPrice));

    for (auto& d : menu) {
        if (d.price <= maxPrice) {
            string s = dishToString(d);
            cout << s << endl;
            logResult(s);
        }
    }
}

// === 6. Показ всего меню ===
void showMenuFile() {
    auto menu = loadMenu();

    cout << "\n======= ВСЕ БЛЮДА В МЕНЮ =======\n";
    logResult("Вывод всего меню:");

    if (menu.empty()) {
        cout << "Меню пустое!\n";
        logResult("Меню пустое.");
        return;
    }

    for (auto& d : menu) {
        string s = dishToString(d);
        cout << s << endl;
        logResult(s);
    }
}

// === Главное меню программы ===
void menu() {
    while (true) {
        cout << "\n===== МЕНЮ ПРОГРАММЫ =====\n"
             << "1. Создать menu.txt\n"
             << "2. Поиск блюда\n"
             << "3. Сортировка меню\n"
             << "4. Добавить блюдо\n"
             << "5. Выборка по цене\n"
             << "6. Показать всё меню\n"
             << "0. Выход\n"
             << "Выбор: ";

        int cmd;
        cin >> cmd;
        cin.ignore();

        switch (cmd) {
            case 1: createMenuFile(); break;
            case 2: searchDish(); break;
            case 3: sortMenu(); break;
            case 4: addDish(); break;
            case 5: filterByPrice(); break;
            case 6: showMenuFile(); break;
            case 0: return;
            default: cout << "Неверная команда!\n";
        }
    }
}

int main() {
    // ЛУЧШИЙ ВАРИАНТ ДЛЯ WINDOWS (поддержка русского)
    system("chcp 1251 > nul");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    menu();
    return 0;
}
