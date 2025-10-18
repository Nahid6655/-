#include <iostream>
#include <climits>
using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    
    cout << "Введите количество строк, а затем количество столбцов: ";
    int N, M, matrix[100][100];
    cin >> N >> M;

    // Ввод элементов матрицы
    cout << "Введите элементы матрицы:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> matrix[i][j];
        }
    }

    // Вывод матрицы
    cout << "Матрица:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // Предварительное вычисление min/max для строк и столбцов
    int rowMin[100], rowMax[100];
    int colMin[100], colMax[100];
    
    // Инициализация
    for (int i = 0; i < N; i++) {
        rowMin[i] = INT_MAX;
        rowMax[i] = INT_MIN;
    }
    for (int j = 0; j < M; j++) {
        colMin[j] = INT_MAX;
        colMax[j] = INT_MIN;
    }
    
    // Вычисление min/max за один проход
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int val = matrix[i][j];
            if (val < rowMin[i]) rowMin[i] = val;
            if (val > rowMax[i]) rowMax[i] = val;
            if (val < colMin[j]) colMin[j] = val;
            if (val > colMax[j]) colMax[j] = val;
        }
    }

    // Поиск седловых точек
    int count = 0;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int v = matrix[i][j];
            
            // Тип A: минимален в строке и максимален в столбце
            if (v == rowMin[i] && v == colMax[j]) {
                cout << "A " << v << " " << i + 1 << " " << j + 1 << endl;
                count++;
            }
            
            // Тип B: максимален в строке и минимален в столбце
            if (v == rowMax[i] && v == colMin[j]) {
                cout << "B " << v << " " << i + 1 << " " << j + 1 << endl;
                count++;
            }
        }
    }

    if (count == 0) {
        cout << "NONE" << endl;
    }

    return 0;
}
