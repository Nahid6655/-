#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string correctCase(const string& text) {
    if (text.empty()) return "";
    
    string result = text;
    bool newSentence = true; // Флаг начала нового предложения
    
    for (int i = 0; i < result.length(); i++) {
        if (newSentence && isalpha(result[i])) {
            // Первая буква предложения - заглавная
            result[i] = toupper(result[i]);
            newSentence = false;
        } else {
            // Остальные буквы - строчные
            result[i] = tolower(result[i]);
        }
        
        // Проверяем конец предложения
        if (result[i] == '.' || result[i] == '!' || result[i] == '?') {
            newSentence = true;
        }
    }
    
    return result;
}

int main() {
    string input;
    cout << "Введите текст: ";
    getline(cin, input);
    
    string corrected = correctCase(input);
    cout << "Исправленный текст: " << corrected << endl;
    
    return 0;
}
