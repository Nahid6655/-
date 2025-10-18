#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

string reverseWords(const string& sentence) {
    stringstream ss(sentence);
    string word;
    string result;
    
    while (ss >> word) {
        // Переворачиваем текущее слово
        reverse(word.begin(), word.end());
        
        // Добавляем перевернутое слово к результату
        if (!result.empty()) {
            result += " ";
        }
        result += word;
    }
    
    return result;
}

int main() {
    string input;
    
    cout << "Введите предложение: ";
    getline(cin, input);
    
    string reversed = reverseWords(input);
    cout << "Результат: " << reversed << endl;
    
    return 0;
}
