#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<vector<int>> matrix(N, vector<int>(M));
    
    // Чтение матрицы
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> matrix[i][j];
        }
    }
    
    // Предварительные вычисления
    vector<int> rowMin(N, INT_MAX);    // минимумы по строкам
    vector<int> rowMax(N, INT_MIN);    // максимумы по строкам  
    vector<int> colMin(M, INT_MAX);    // минимумы по столбцам
    vector<int> colMax(M, INT_MIN);    // максимумы по столбцам
    
    // Вычисляем min/max для каждой строки и каждого столбца
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int val = matrix[i][j];
            
            // Обновляем min/max для строки i
            if (val < rowMin[i]) rowMin[i] = val;
            if (val > rowMax[i]) rowMax[i] = val;
            
            // Обновляем min/max для столбца j
            if (val < colMin[j]) colMin[j] = val;
            if (val > colMax[j]) colMax[j] = val;
        }
    }
    
    // Поиск седловых точек
    bool found = false;
    
    // Проверяем каждый элемент матрицы
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int val = matrix[i][j];
            
            // Тип A: минимален в строке и максимален в столбце
            if (val == rowMin[i] && val == colMax[j]) {
                cout << "A " << val << " " << i + 1 << " " << j + 1 << endl;
                found = true;
            }
            
            // Тип B: максимален в строке и минимален в столбце  
            if (val == rowMax[i] && val == colMin[j]) {
                cout << "B " << val << " " << i + 1 << " " << j + 1 << endl;
                found = true;
            }
        }
    }
    
    if (!found) {
        cout << "NONE" << endl;
    }
    
    return 0;
}
