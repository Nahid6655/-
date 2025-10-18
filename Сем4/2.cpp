#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    vector<vector<int>> matrix(N, vector<int>(N));
    
    // Чтение матрицы
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> matrix[i][j];
        }
    }
    
    // Вычисляем эталонную сумму (первая строка)
    int targetSum = 0;
    for (int j = 0; j < N; j++) {
        targetSum += matrix[0][j];
    }
    
    // Проверяем суммы всех строк
    for (int i = 1; i < N; i++) {
        int rowSum = 0;
        for (int j = 0; j < N; j++) {
            rowSum += matrix[i][j];
        }
        if (rowSum != targetSum) {
            cout << "NO" << endl;
            return 0;
        }
    }
    
    // Проверяем суммы всех столбцов
    for (int j = 0; j < N; j++) {
        int colSum = 0;
        for (int i = 0; i < N; i++) {
            colSum += matrix[i][j];
        }
        if (colSum != targetSum) {
            cout << "NO" << endl;
            return 0;
        }
    }
    
    // Проверяем главную диагональ
    int mainDiagSum = 0;
    for (int i = 0; i < N; i++) {
        mainDiagSum += matrix[i][i];
    }
    if (mainDiagSum != targetSum) {
        cout << "NO" << endl;
        return 0;
    }
    
    // Проверяем побочную диагональ
    int antiDiagSum = 0;
    for (int i = 0; i < N; i++) {
        antiDiagSum += matrix[i][N - 1 - i];
    }
    if (antiDiagSum != targetSum) {
        cout << "NO" << endl;
        return 0;
    }
    
    // Если все проверки пройдены
    cout << "YES " << targetSum << endl;
    
    return 0;
}
