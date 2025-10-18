#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    // Система уравнений:
    // 2x + 3y = 13
    // 5x - y = 9
    
    double a1 = 2, b1 = 3, c1 = 13;
    double a2 = 5, b2 = -1, c2 = 9;
    
    // Вычисляем определители
    double main_det = a1 * b2 - a2 * b1;    // Главный определитель
    double det_x = c1 * b2 - c2 * b1;       // Определитель для x
    double det_y = a1 * c2 - a2 * c1;       // Определитель для y
    
    // Проверяем, имеет ли система решение
    if (main_det == 0) {
        if (det_x == 0 && det_y == 0) {
            cout << "Система имеет бесконечно много решений" << endl;
        } else {
            cout << "Система не имеет решений" << endl;
        }
    } else {
        // Находим решение
        double x = det_x / main_det;
        double y = det_y / main_det;
        
        // Вывод результатов
        cout << "Решение системы уравнений:" << endl;
        cout << fixed << setprecision(1);
        cout << a1 << "x + " << b1 << "y = " << c1 << endl;
        cout << a2 << "x + " << b2 << "y = " << c2 << endl;
        cout << "\nРезультат:" << endl;
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        
    
    return 0;
}
