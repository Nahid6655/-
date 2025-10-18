#include <iostream>
#include <string>

using namespace std;

bool containsAllChars(const string& A, const string& B) {
    // Проверяем каждый символ строки B
    for (int i = 0; i < B.length(); i++) {
        char currentChar = B[i];
        bool found = false;
        
        // Ищем текущий символ в строке A
        for (int j = 0; j < A.length(); j++) {
            if (A[j] == currentChar) {
                found = true;
                break;
            }
        }
        
        // Если символ не найден в A, возвращаем false
        if (!found) {
            return false;
        }
    }
    
    // Все символы из B найдены в A
    return true;
}

int main() {
    string A, B;
    
    cout << "Введите строку A: ";
    getline(cin, A);
    
    cout << "Введите строку B: ";
    getline(cin, B);
    
    if (containsAllChars(A, B)) {
        cout << "Да" << endl;
    } else {
        cout << "Нет" << endl;
    }
    
    return 0;
}
