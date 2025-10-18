#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
    // Функция для подсчета площади треугольника
    double area = 0.5 * abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
    return area;
}

int main()
{
    setlocale(LC_ALL, "RU");

    // Задача 1: Площадь треугольника по координатам вершин
    double coord[3][2];

    cout << "Введите координаты вершин треугольника" << endl;

    for (int i = 0; i < 3; i++) {
        cout << "Вершина " << i + 1 << " (x, y): ";
        cin >> coord[i][0] >> coord[i][1];
    }

    // Извлекаем координаты
    double x1 = coord[0][0], y1 = coord[0][1];
    double x2 = coord[1][0], y2 = coord[1][1];
    double x3 = coord[2][0], y3 = coord[2][1];

    // Вычисляем площадь (ПРАВИЛЬНЫЙ порядок параметров)
    double area = triangle(x1, y1, x2, y2, x3, y3);
    
    cout << fixed << setprecision(2);
    cout << "Площадь треугольника: " << area << endl;
    
    return 0;
}
