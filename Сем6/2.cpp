#include <iostream>
#include <string>

using namespace std;

int countUniqueChars(const string& str) {
    int count = 0;
    int n = str.length();
    
    for (int i = 0; i < n; i++) {
        // Проверяем, встречался ли текущий символ ранее
        bool isUnique = true;
        for (int j = 0; j < i; j++) {
            if (str[i] == str[j]) {
                isUnique = false;
                break;
            }
        }
        
        // Если символ уникальный, увеличиваем счетчик
        if (isUnique) {
            count++;
        }
    }
    
    return count;
}

int main() {
    string input;
    cout << "Введите строку: ";
    cin >> input;
    
    int result = countUniqueChars(input);
    cout << "Количество уникальных символов: " << result << endl;
    
    return 0;
}
