#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string removeDigits(const string& str) {
    string result = str; // Создаем копию строки для модификации
    int writeIndex = 0;  // Индекс для записи
    
    for (int readIndex = 0; readIndex < str.length(); readIndex++) {
        // Если текущий символ НЕ цифра - копируем его
        if (!isdigit(str[readIndex])) {
            result[writeIndex] = str[readIndex];
            writeIndex++;
        }
    }
    
    // Обрезаем строку до новой длины
    result.resize(writeIndex);
    return result;
}

int main() {
    string input;
    cout << "Введите строку: ";
    getline(cin, input);
    
    string result = removeDigits(input);
    cout << "Результат: " << result << endl;
    
    return 0;
}
