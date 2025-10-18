#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");
    
    double x1, y1, x2, y2, x3, y3;

    // Ввод координат
    cout << "Введите координаты первой точки (x1, y1): ";
    cin >> x1 >> y1;
    cout << "Введите координаты второй точки (x2, y2): ";  // Исправлено: "второй точки"
    cin >> x2 >> y2;
    cout << "Введите координаты третьей точки (x3, y3): "; // Исправлено: "третьей точки"
    cin >> x3 >> y3;

    // Вычисляем векторы AB, AC
    double ab_x = x2 - x1;
    double ab_y = y2 - y1;
    double ac_x = x3 - x1;
    double ac_y = y3 - y1;

    // Векторное произведение векторов
    double cross_product = ab_x * ac_y - ac_x * ab_y;

    // Проверка с учетом погрешности вычислений
    if (abs(cross_product) < 1e-10)  // Добавлен abs() и проверка на малую величину
        cout << "Точки лежат на одной прямой\n";
    else
        cout << "Точки не лежат на одной прямой\n";

    return 0;
}
