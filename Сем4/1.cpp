#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");

    int N = 0;
    double matrix[100][100];
    double matrix_1[100][100];
    double matrix_2[100][100];
    double matrix_3[100][100];
    double matrix_4[100][100];

    cout << "Введите порядок матрицы: ";
    cin >> N;

    // Ввод элементов матрицы
    cout << "Введите элементы матрицы:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> matrix[i][j];
        }
    }
    
    // Вывод исходной матрицы
    cout << "\nИсходная матрица:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // 1. Отражение относительно главной диагонали (транспонирование)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix_1[i][j] = matrix[j][i];
        }
    }

    cout << "\n1. Отражение относительно главной диагонали:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matrix_1[i][j] << " ";
        }
        cout << endl;
    }

    // 2. Отражение относительно побочной диагонали
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix_2[i][j] = matrix[N - 1 - j][N - 1 - i];
        }
    }

    cout << "\n2. Отражение относительно побочной диагонали:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matrix_2[i][j] << " ";
        }
        cout << endl;
    }

    // 3. Зеркальное отражение относительно вертикальной оси
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix_3[i][j] = matrix[i][N - 1 - j];
        }
    }

    cout << "\n3. Зеркальное отражение относительно вертикальной оси:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matrix_3[i][j] << " ";
        }
        cout << endl;
    }

    // 4. Зеркальное отражение относительно горизонтальной оси
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix_4[i][j] = matrix[N - 1 - i][j];
        }
    }

    cout << "\n4. Зеркальное отражение относительно горизонтальной оси:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matrix_4[i][j] << " ";
        }
        cout << endl;
    }

    // Сравнение матриц попарно
    cout << "\n=== СРАВНЕНИЕ МАТРИЦ ===" << endl;
    
    bool foundMatch = false;
    
    // Сравнение матриц 1 и 2
    bool match12 = true;
    for (int i = 0; i < N && match12; i++) {
        for (int j = 0; j < N && match12; j++) {
            if (matrix_1[i][j] != matrix_2[i][j]) {
                match12 = false;
            }
        }
    }
    if (match12) {
        cout << "(1, 2)" << endl;
        foundMatch = true;
    }
    
    // Сравнение матриц 1 и 3
    bool match13 = true;
    for (int i = 0; i < N && match13; i++) {
        for (int j = 0; j < N && match13; j++) {
            if (matrix_1[i][j] != matrix_3[i][j]) {
                match13 = false;
            }
        }
    }
    if (match13) {
        cout << "(1, 3)" << endl;
        foundMatch = true;
    }
    
    // Сравнение матриц 1 и 4
    bool match14 = true;
    for (int i = 0; i < N && match14; i++) {
        for (int j = 0; j < N && match14; j++) {
            if (matrix_1[i][j] != matrix_4[i][j]) {
                match14 = false;
            }
        }
    }
    if (match14) {
        cout << "(1, 4)" << endl;
        foundMatch = true;
    }
    
    // Сравнение матриц 2 и 3
    bool match23 = true;
    for (int i = 0; i < N && match23; i++) {
        for (int j = 0; j < N && match23; j++) {
            if (matrix_2[i][j] != matrix_3[i][j]) {
                match23 = false;
            }
        }
    }
    if (match23) {
        cout << "(2, 3)" << endl;
        foundMatch = true;
    }
    
    // Сравнение матриц 2 и 4
    bool match24 = true;
    for (int i = 0; i < N && match24; i++) {
        for (int j = 0; j < N && match24; j++) {
            if (matrix_2[i][j] != matrix_4[i][j]) {
                match24 = false;
            }
        }
    }
    if (match24) {
        cout << "(2, 4)" << endl;
        foundMatch = true;
    }
    
    // Сравнение матриц 3 и 4
    bool match34 = true;
    for (int i = 0; i < N && match34; i++) {
        for (int j = 0; j < N && match34; j++) {
            if (matrix_3[i][j] != matrix_4[i][j]) {
                match34 = false;
            }
        }
    }
    if (match34) {
        cout << "(3, 4)" << endl;
        foundMatch = true;
    }
    
   
