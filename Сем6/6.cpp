#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string caesarCipher(const string& text, int shift) {
    string result = "";
    
    // Обрабатываем отрицательный сдвиг и сдвиги больше 26
    shift = shift % 26;
    if (shift < 0) {
        shift += 26; // Преобразуем отрицательный сдвиг в положительный
    }
    
    for (char c : text) {
        if (isupper(c)) {
            // Для заглавных букв
            char base = 'A';
            char encrypted = (c - base + shift) % 26 + base;
            result += encrypted;
        }
        else if (islower(c)) {
            // Для строчных букв
            char base = 'a';
            char encrypted = (c - base + shift) % 26 + base;
            result += encrypted;
        }
        else {
            // Все остальные символы остаются без изменений
            result += c;
        }
    }
    
    return result;
}

int main() {
    string text;
    int shift;
    
    cout << "Введите текст: ";
    getline(cin, text);
    
    cout << "Введите сдвиг: ";
    cin >> shift;
    
    string encrypted = caesarCipher(text, shift);
    cout << "Зашифрованный текст: " << encrypted << endl;
    
    // Демонстрация дешифрования
    string decrypted = caesarCipher(encrypted, -shift);
    cout << "Расшифрованный текст: " << decrypted << endl;
    
    return 0;
}
