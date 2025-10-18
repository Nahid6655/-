#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Функция для вычисления расстояния между двумя точками
double calculateDistance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    setlocale(LC_ALL, "RU");
    
    double x1, y1, x2, y2;

    cout << "Введите координаты первой точки (x1 y1): ";
    cin >> x1 >> y1;
    
    cout << "Введите координаты второй точки (x2 y2): ";
    cin >> x2 >> y2;

    // Проверка корректности ввода
    if (cin.fail()) {
        cout << "Ошибка ввода! Пожалуйста, введите числа." << endl;
        return 1;
    }

    double distance = calculateDistance(x1, y1, x2, y2);

    cout << fixed << setprecision(2);
    cout << "Расстояние между (" << x1 << ", " << y1 << ") и (" 
         << x2 << ", " << y2 << ") равняется " << distance << endl;

    return 0;
}
