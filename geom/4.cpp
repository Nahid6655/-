#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Функция для вычисления расстояния между двумя точками
double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main() {
    setlocale(LC_ALL, "RU");
    
    double rect[4][2];
    
    cout << "Введите координаты 4 вершин прямоугольника:" << endl;
    
    for (int i = 0; i < 4; i++) {
        cout << "Вершина " << i + 1 << " (x y): ";
        cin >> rect[i][0] >> rect[i][1];
    }
    
    // Находим противоположные вершины (самые удаленные)
    // Для прямоугольника достаточно найти расстояние между первой и третьей вершинами
    // или между второй и четвертой вершинами
    double diagonal1 = distance(rect[0][0], rect[0][1], rect[2][0], rect[2][1]);
    double diagonal2 = distance(rect[1][0], rect[1][1], rect[3][0], rect[3][1]);
    
    // В прямоугольнике диагонали равны, поэтому берем любую
    double diagonal = diagonal1;
    
    cout << fixed << setprecision(2);
    cout << "Длина диагонали прямоугольника: " << diagonal << endl;
    
    return 0;
}
