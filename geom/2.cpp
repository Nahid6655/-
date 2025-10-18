#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Функция для вычисления расстояния между двумя точками
double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Функция для вычисления периметра многоугольника
double calculatePerimeter(double coords[][2], int vertices) {
    double perimeter = 0.0;
    
    // Вычисляем расстояния между соседними вершинами
    for (int i = 0; i < vertices; i++) {
        int next = (i + 1) % vertices; // Следующая вершина (для замыкания многоугольника)
        double side = distance(coords[i][0], coords[i][1], coords[next][0], coords[next][1]);
        perimeter += side;
    }
    
    return perimeter;
}

int main() {
    setlocale(LC_ALL, "RU");
    
    const int VERTICES = 4; // Количество вершин многоугольника
    double coords[VERTICES][2];
    
    cout << "Введите координаты " << VERTICES << " вершин многоугольника:" << endl;
    
    for (int i = 0; i < VERTICES; i++) {
        cout << "Вершина " << i + 1 << " (x y): ";
        cin >> coords[i][0] >> coords[i][1];
    }
    
    double perimeter = calculatePerimeter(coords, VERTICES);
    
    cout << fixed << setprecision(2);
    cout << "Периметр многоугольника: " << perimeter << endl;
    
    return 0;
}
