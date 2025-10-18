#include <iostream>
#include <string>

using namespace std;

string compressRLE(const string& str) {
    if (str.empty()) return "";
    
    string compressed = "";
    int count = 1;
    char current = str[0];
    
    for (int i = 1; i < str.length(); i++) {
        if (str[i] == current) {
            count++;
        } else {
            // Добавляем символ и количество в результат
            compressed += current;
            compressed += to_string(count);
            
            // Начинаем считать новые символы
            current = str[i];
            count = 1;
        }
    }
    
    // Добавляем последнюю последовательность
    compressed += current;
    compressed += to_string(count);
    
    return compressed;
}

int main() {
    string input;
    cout << "Введите строку для сжатия: ";
    cin >> input;
    
    string compressed = compressRLE(input);
    cout << "Сжатая строка: " << compressed << endl;
    
    return 0;
}
