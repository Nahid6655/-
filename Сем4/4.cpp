#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    int matrix[100][100] = {0};
    
    // Направления: вправо, вниз, влево, вверх
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int currentDirection = 0; // начинаем движение вправо
    
    int row = 0, col = 0; // начальная позиция
    int num = 1; // начинаем с 1
    
    while (num <= N * N) {
        matrix[row][col] = num++;
        
        // Пробуем двигаться в текущем направлении
        int nextRow = row + directions[currentDirection][0];
        int nextCol = col + directions[currentDirection][1];
        
        // Если вышли за границы или клетка уже заполнена, меняем направление
        if (nextRow < 0 || nextRow >= N || nextCol < 0 || nextCol >= N || matrix[nextRow][nextCol] != 0) {
            currentDirection = (currentDirection + 1) % 4;
            nextRow = row + directions[currentDirection][0];
            nextCol = col + directions[currentDirection][1];
        }
        
        row = nextRow;
        col = nextCol;
    }
    
    // Вывод матрицы
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(3) << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
