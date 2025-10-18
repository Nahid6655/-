#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> findUniqueSubstrings(const string& str, int k) {
    vector<string> result;
    int n = str.length();
    
    // Проверяем, что k не больше длины строки
    if (k > n) {
        return result;
    }
    
    // Проходим по всем возможным подстрокам длины k
    for (int i = 0; i <= n - k; i++) {
        string substring = str.substr(i, k);
        bool allUnique = true;
        
        // Проверяем, все ли символы в подстроке уникальны
        for (int j = 0; j < k && allUnique; j++) {
            for (int m = j + 1; m < k; m++) {
                if (substring[j] == substring[m]) {
                    allUnique = false;
                    break;
                }
            }
        }
        
        // Если все символы уникальны, добавляем в результат
        if (allUnique) {
            result.push_back(substring);
        }
    }
    
    return result;
}

int main() {
    string input;
    int k;
    
    cout << "Введите строку: ";
    cin >> input;
    cout << "Введите длину k: ";
    cin >> k;
    
    vector<string> uniqueSubstrings = findUniqueSubstrings(input, k);
    
    if (uniqueSubstrings.empty()) {
        cout << "Подстрок длины " << k << " с уникальными символами не найдено" << endl;
    } else {
        cout << "Подстроки длины " << k << " с уникальными символами:" << endl;
        for (const string& substr : uniqueSubstrings) {
            cout << substr << endl;
        }
    }
    
    return 0;
}
