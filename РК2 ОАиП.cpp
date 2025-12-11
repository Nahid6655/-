#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <limits>

using namespace std;

// БАЗОВЫЙ КЛАСС

class MusicalInstrument {
protected:
    string name;
    string material;
    double price;
    vector<string> owners;  // композиция

public:
    MusicalInstrument(string n, string m, double p, vector<string> o)
        : name(n), material(m), price(p), owners(o) {
    }

    virtual ~MusicalInstrument() = default;

    virtual void display() const {
        cout << "Name: " << name
            << ", Material: " << material
            << ", Price: " << price
            << ", Owners: ";
        for (auto& o : owners) cout << o << " ";
        cout << "\n";
    }

    virtual string getType() const = 0;

    virtual void saveToFile(ostream& out) const = 0;

    void changeMaterial(const string& m) { material = m; }
    void changePrice(double p) { price = p; }
    void addOwner(const string& o) { owners.push_back(o); }

    string getMaterial() const { return material; }
    double getPrice() const { return price; }
};


// СТРУННЫЙ ИНСТРУМЕНТ 
class StringInstrument : public MusicalInstrument {
    int strings;
    string tuning;

public:
    StringInstrument(string n, string m, double p, int s, string t, vector<string> o)
        : MusicalInstrument(n, m, p, o), strings(s), tuning(t) {
    }

    void display() const override {
        cout << "[STRING] ";
        MusicalInstrument::display();
        cout << "   Strings: " << strings
            << ", Tuning: " << tuning << "\n";
    }

    string getType() const override { return "String"; }

    int getStrings() const { return strings; }
    string getTuning() const { return tuning; }

    void saveToFile(ostream& out) const override {
        out << "String;" << name << ";" << material << ";" << price
            << ";" << strings << "-" << tuning << ";";

        for (int i = 0; i < owners.size(); i++) {
            out << owners[i];
            if (i + 1 < owners.size()) out << "|";
        }
        out << "\n";
    }
};

// ДУХОВОЙ ИНСТРУМЕНТ

class BrassInstrument : public MusicalInstrument {
    string brassType;
    int tubeLength;

public:
    BrassInstrument(string n, string m, double p, string bt, int tl, vector<string> o)
        : MusicalInstrument(n, m, p, o), brassType(bt), tubeLength(tl) {
    }

    void display() const override {
        cout << "[BRASS] ";
        MusicalInstrument::display();
        cout << "   Brass type: " << brassType
            << ", Tube length: " << tubeLength << "\n";
    }

    string getType() const override { return "Brass"; }

    int getTubeLength() const { return tubeLength; }

    void saveToFile(ostream& out) const override {
        out << "Brass;" << name << ";" << material << ";" << price
            << ";" << brassType << "-" << tubeLength << ";";

        for (int i = 0; i < owners.size(); i++) {
            out << owners[i];
            if (i + 1 < owners.size()) out << "|";
        }
        out << "\n";
    }
};

// ГЛОБАЛЬНАЯ КОЛЛЕКЦИЯ

vector<shared_ptr<MusicalInstrument>> catalog;

// ЗАГРУЗКА ИНСТРУМЕНТОВ

void loadFile(const string& filename)
{
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Ошибка: не удалось открыть файл!\n";
        return;
    }

    catalog.clear();
    string line;

    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string type, name, material, priceStr, param, ownersStr;

        getline(ss, type, ';');
        getline(ss, name, ';');
        getline(ss, material, ';');
        getline(ss, priceStr, ';');
        getline(ss, param, ';');
        getline(ss, ownersStr);

        double price = stod(priceStr);

        vector<string> owners;
        string owner;
        stringstream oss(ownersStr);
        while (getline(oss, owner, '|'))
            owners.push_back(owner);

        if (type == "String") {
            auto dash = param.find('-');
            int strings = stoi(param.substr(0, dash));
            string tuning = param.substr(dash + 1);

            catalog.push_back(make_shared<StringInstrument>(name, material, price, strings, tuning, owners));
        }
        else if (type == "Brass") {
            auto dash = param.find('-');
            string brassType = param.substr(0, dash);
            int length = stoi(param.substr(dash + 1));

            catalog.push_back(make_shared<BrassInstrument>(name, material, price, brassType, length, owners));
        }
    }

    cout << "Файл успешно загружен.\n";
}

// СОХРАНЕНИЕ В ФАЙЛ

void saveFile(const string& filename)
{
    ofstream out(filename);
    for (auto& inst : catalog)
        inst->saveToFile(out);

    cout << "Сохранено в файл.\n";
}


// ВЫВОД ВСЕХ ИНСТРУМЕНТОВ

void showAll()
{
    cout << "=== Каталог инструментов ===\n";
    for (int i = 0; i < catalog.size(); i++) {
        cout << "#" << i << " ";
        catalog[i]->display();
    }
}

//  ФИЛЬТР ПО МАТЕРИАЛУ И ЦЕНЕ 

void filterWood600()
{
    cout << "Инструменты из Wood, цена > 600:\n";

    vector<shared_ptr<MusicalInstrument>> res;

    copy_if(catalog.begin(), catalog.end(), back_inserter(res),
        [](auto& i) {
            return i->getMaterial() == "Wood" && i->getPrice() > 600;
        });

    for (auto& i : res) i->display();
}

//  ПОИСК СТРУННОГО С МАКС. СТРУНАМИ 

void maxStrings()
{
    vector<shared_ptr<StringInstrument>> s;

    for (auto& inst : catalog)
        if (inst->getType() == "String")
            s.push_back(dynamic_pointer_cast<StringInstrument>(inst));

    if (s.empty()) {
        cout << "Нет струнных инструментов.\n";
        return;
    }

    auto it = max_element(s.begin(), s.end(),
        [](auto& a, auto& b) {
            return a->getStrings() < b->getStrings();
        });

    cout << "Струнный с максимальным числом струн:\n";
    (*it)->display();
}

//  ПОИСК ДУХОВОГО С МАКС. ТРУБОЙ

void maxTube()
{
    vector<shared_ptr<BrassInstrument>> b;

    for (auto& inst : catalog)
        if (inst->getType() == "Brass")
            b.push_back(dynamic_pointer_cast<BrassInstrument>(inst));

    if (b.empty()) {
        cout << "Нет духовых инструментов.\n";
        return;
    }

    auto it = max_element(b.begin(), b.end(),
        [](auto& a, auto& b) {
            return a->getTubeLength() < b->getTubeLength();
        });

    cout << "Духовой с самой длинной трубой:\n";
    (*it)->display();
}

//  СОРТИРОВКА ПО ЦЕНЕ

void sortByPrice()
{
    sort(catalog.begin(), catalog.end(),
        [](auto& a, auto& b) { return a->getPrice() < b->getPrice(); });

    cout << "Отсортировано по цене.\n";
}

//  СОРТИРОВКА СТРУННЫХ ПО СТРОЮ+ЦЕНЕ 

void sortStringsAdvanced()
{
    vector<shared_ptr<StringInstrument>> s;

    for (auto& inst : catalog)
        if (inst->getType() == "String")
            s.push_back(dynamic_pointer_cast<StringInstrument>(inst));

    sort(s.begin(), s.end(),
        [](auto& a, auto& b) {
            if (a->getTuning() == b->getTuning())
                return a->getPrice() < b->getPrice();
            return a->getTuning() < b->getTuning();
        });

    cout << "Отсортированные струнные:\n";
    for (auto& x : s) x->display();
}

//  ДОБАВЛЕНИЕ НОВОГО ИНСТРУМЕНТА 

void addInstrument()
{
    string type;
    cout << "Введите тип (String/Brass): ";
    cin >> type;

    string name, material;
    double price;

    cout << "Название: ";
    cin >> name;
    cout << "Материал: ";
    cin >> material;
    cout << "Цена: ";
    cin >> price;

    vector<string> owners;
    cout << "Введите первого владельца: ";
    string o; cin >> o;
    owners.push_back(o);

    if (type == "String") {
        int s; string t;
        cout << "Количество струн: ";
        cin >> s;
        cout << "Строй: ";
        cin >> t;

        catalog.push_back(make_shared<StringInstrument>(name, material, price, s, t, owners));
    }
    else {
        string bt; int len;
        cout << "Тип латуни: ";
        cin >> bt;
        cout << "Длина трубы: ";
        cin >> len;

        catalog.push_back(make_shared<BrassInstrument>(name, material, price, bt, len, owners));
    }

    cout << "Добавлено.\n";
}

//  РЕДАКТИРОВАНИЕ 

void editInstrument()
{
    showAll();

    cout << "Введите индекс инструмента: ";
    int id; cin >> id;

    if (id < 0 || id >= catalog.size()) {
        cout << "Неверный индекс.\n";
        return;
    }

    double newPrice;
    string newMaterial, newOwner;

    cout << "Новая цена: ";
    cin >> newPrice;
    cout << "Новый материал: ";
    cin >> newMaterial;
    cout << "Новый владелец: ";
    cin >> newOwner;

    catalog[id]->changePrice(newPrice);
    catalog[id]->changeMaterial(newMaterial);
    catalog[id]->addOwner(newOwner);

    cout << "Изменения сохранены.\n";
}

//  УДАЛЕНИЕ 

void removeInstrument()
{
    showAll();
    cout << "Введите индекс для удаления: ";
    int id; cin >> id;

    if (id >= 0 && id < catalog.size()) {
        catalog.erase(catalog.begin() + id);
        cout << "Удалено.\n";
    }
    else {
        cout << "Неверный индекс.\n";
    }
}

//  МЕНЮ 

int main()
{
    setlocale(0, "");

    while (true) {
        cout << "\n==== МЕНЮ ====\n"
            << "1. Загрузить из файла\n"
            << "2. Показать все\n"
            << "3. Фильтр Wood & >600\n"
            << "4. Сортировка по цене\n"
            << "5. Макс. число струн\n"
            << "6. Макс. длина трубы\n"
            << "7. Добавить\n"
            << "8. Редактировать\n"
            << "9. Удалить\n"
            << "10. Сохранить в файл\n"
            << "11. Сортировать струнные (строй + цена)\n"
            << "0. Выход\n> ";

        int c;
        cin >> c;

        switch (c) {
        case 0: return 0;
        case 1: loadFile("catalog.txt"); break;
        case 2: showAll(); break;
        case 3: filterWood600(); break;
        case 4: sortByPrice(); break;
        case 5: maxStrings(); break;
        case 6: maxTube(); break;
        case 7: addInstrument(); break;
        case 8: editInstrument(); break;
        case 9: removeInstrument(); break;
        case 10: saveFile("catalog_out.txt"); break;
        case 11: sortStringsAdvanced(); break;
        default: cout << "Неверный пункт.\n";
        }
    }
}
