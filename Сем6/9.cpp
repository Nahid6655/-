#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string findLongestCommonSubstring(const string& str1, const string& str2) {
    int m = str1.length();
    int n = str2.length();
    
    // Создаем DP таблицу
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    int maxLength = 0;    // Длина наибольшей общей подстроки
    int endIndex = 0;     // Конечный индекс в str1
    
    // Заполняем DP таблицу
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i - 1; // Сохраняем конечный индекс в str1
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }
    
    // Извлекаем наибольшую общую подстроку
    if (maxLength == 0) {
        return ""; // Нет общей подстроки
    }
    
    return str1.substr(endIndex - maxLength + 1, maxLength);
}

int main() {
    string str1, str2;
    
    cout << "Введите первую строку: ";
    cin >> str1;
    cout << "Введите вторую строку: ";
    cin >> str2;
    
    string result = findLongestCommonSubstring(str1, str2);
    
    cout << "Наибольшая общая подстрока: \"" << result << "\"" << endl;
    cout << "Длина: " << result.length() << endl;
    
    return 0;
}
