#include <iostream>
using namespace std;

// Функция для проверки пересечения двух отрезков
bool doSegmentsIntersect(double Ax, double Ay, double Bx, double By,
                        double Cx, double Cy, double Dx, double Dy) {
    // Векторные произведения для проверки взаимного расположения
    double v1 = (Bx - Ax) * (Cy - Ay) - (By - Ay) * (Cx - Ax); // AB × AC
    double v2 = (Bx - Ax) * (Dy - Ay) - (By - Ay) * (Dx - Ax); // AB × AD
    double v3 = (Dx - Cx) * (Ay - Cy) - (Dy - Cy) * (Ax - Cx); // CD × CA
    double v4 = (Dx - Cx) * (By - Cy) - (Dy - Cy) * (Bx - Cx); // CD × CB

    // Отрезки пересекаются, если точки лежат по разные стороны от другого отрезка
    return (v1 * v2 < 0) && (v3 * v4 < 0);
}

// Функция для проверки пересечения двух многоугольников
bool doPolygonsIntersect(double x1[], double y1[], int n1, 
                        double x2[], double y2[], int n2) {
    // Проверяем все пары ребер
    for (int i = 0; i < n1; i++) {
        double Ax = x1[i], Ay = y1[i];
        double Bx = x1[(i + 1) % n1], By = y1[(i + 1) % n1];

        for (int j = 0; j < n2; j++) {
            double Cx = x2[j], Cy = y2[j];
            double Dx = x2[(j + 1) % n2], Dy = y2[(j + 1) % n2];

            if (doSegmentsIntersect(Ax, Ay, Bx, By, Cx, Cy, Dx, Dy)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    setlocale(LC_ALL, "RU");
    
    int n1, n2;
    double x1[100], y1[100], x2[100], y2[100];

    // Ввод первого многоугольника
    cout << "Введите количество вершин первого многоугольника (до 100): ";
    cin >> n1;
    if (n1 < 3 || n1 > 100) {
        cout << "Ошибка: количество вершин должно быть от 3 до 100" << endl;
        return 1;
    }
    
    for (int i = 0; i < n1; i++) {
        cout << "Вершина " << i + 1 << " первого многоугольника (x y): ";
        cin >> x1[i] >> y1[i];
    }

    // Ввод второго многоугольника
    cout << "Введите количество вершин второго многоугольника (до 100): ";
    cin >> n2;
    if (n2 < 3 || n2 > 100) {
        cout << "Ошибка: количество вершин должно быть от 3 до 100" << endl;
        return 1;
    }
    
    for (int i = 0; i < n2; i++) {
        cout << "Вершина " << i + 1 << " второго многоугольника (x y): ";
        cin >> x2[i] >> y2[i];
    }

    // Проверка пересечения
    if (doPolygonsIntersect(x1, y1, n1, x2, y2, n2)) {
        cout << "Многоугольники ПЕРЕСЕКАЮТСЯ" << endl;
    } else {
        cout << "Многоугольники НЕ пересекаются" << endl;
    }

    return 0;
}
