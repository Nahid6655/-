#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isPalindrome(const char str[]) {
    int left = 0;
    int right = 0;
    
    // Находим длину строки
    while (str[right] != '\0') {
        right++;
    }
    right--; // Перемещаемся на последний символ
    
    while (left < right) {
        // Пропускаем пробелы слева
        while (left < right && str[left] == ' ') {
            left++;
        }
        // Пропускаем пробелы справа
        while (left < right && str[right] == ' ') {
            right--;
        }
        
        // Сравниваем символы (игнорируя регистр)
        if (tolower(str[left]) != tolower(str[right])) {
            return false; // Не палиндром
        }
        
        left++;
        right--;
    }
    
    return true; // Палиндром
}

int main() {
    const int MAX_SIZE = 1000;
    char input[MAX_SIZE];
    
    cout << "Введите строку: ";
    cin.getline(input, MAX_SIZE);
    
    if (isPalindrome(input)) {
        cout << "Палиндром" << endl;
    } else {
        cout << "Не палиндром" << endl;
    }
    
    return 0;
}
