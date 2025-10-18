#include <iostream>
#include <cmath>
using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    double x1, y1, x2, y2, x3, y3, x4, y4;

    cout << "Введите координаты точки A (x1 y1): ";
    cin >> x1 >> y1;

    cout << "Введите координаты точки B (x2 y2): ";
    cin >> x2 >> y2;

    cout << "Введите координаты точки C (x3 y3): ";
    cin >> x3 >> y3;

    cout << "Введите координаты точки D (x4 y4): ";
    cin >> x4 >> y4;

    // Вычисляем векторные произведения (ориентированные площади треугольников)
    double v1 = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3); // Треугольник C-D-A
    double v2 = (x4 - x3) * (y2 - y3) - (y4 - y3) * (x2 - x3); // Треугольник C-D-B
    double v3 = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1); // Треугольник A-B-C
    double v4 = (x2 - x1) * (y4 - y1) - (y2 - y1) * (x4 - x1); // Треугольник A-B-D

    // Проверяем пересечение
    if ((v1 * v2 < 0) && (v3 * v4 < 0)) {
        cout << "Отрезки пересекаются" << endl;
    }
    else {
        cout << "Отрезки не пересекаются" << endl;
    }

    return 0;
}
