#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool isVowel(char c) {
    c = tolower(c); // Приводим к нижнему регистру для удобства проверки
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

bool isConsonant(char c) {
    c = tolower(c);
    // Согласная - это буква английского алфавита, которая не гласная
    return (c >= 'a' && c <= 'z' && !isVowel(c));
}

int main() {
    string input;
    cout << "Введите строку: ";
    getline(cin, input);
    
    int vowels = 0;
    int consonants = 0;
    
    for (char c : input) {
        if (isVowel(c)) {
            vowels++;
        } else if (isConsonant(c)) {
            consonants++;
        }
    }
    
    cout << "Гласных: " << vowels << endl;
    cout << "Согласных: " << consonants << endl;
    
    return 0;
}
