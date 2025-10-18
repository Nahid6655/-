#include <iostream>
#include <iomanip>

using namespace std;

// Функция для вычисления определителя матрицы 3x3
double determinant(double a11, double a12, double a13,
                   double a21, double a22, double a23,
                   double a31, double a32, double a33) {
    return a11 * (a22 * a33 - a23 * a32)
         - a12 * (a21 * a33 - a23 * a31)
         + a13 * (a21 * a32 - a22 * a31);
}

int main() {
    // Коэффициенты системы
    double a1 = 1, b1 = 1, c1 = 1, d1 = 6;
    double a2 = 2, b2 = -1, c2 = 3, d2 = 14;
    double a3 = -1, b3 = 4, c3 = -1, d3 = 2;
    
    // Вычисляем определители
    double main_det = determinant(a1, b1, c1, a2, b2, c2, a3, b3, c3);
    double det_x = determinant(d1, b1, c1, d2, b2, c2, d3, b3, c3);
    double det_y = determinant(a1, d1, c1, a2, d2, c2, a3, d3, c3);
    double det_z = determinant(a1, b1, d1, a2, b2, d2, a3, b3, d3);
    
    cout << "Система уравнений:" << endl;
    cout << a1 << "x + " << b1 << "y + " << c1 << "z = " << d1 << endl;
    cout << a2 << "x + " << b2 << "y + " << c2 << "z = " << d2 << endl;
    cout << a3 << "x + " << b3 << "y + " << c3 << "z = " << d3 << endl;
    
    cout << fixed << setprecision(6);
    cout << "\nОпределители:" << endl;
    cout << "Δ = " << main_det << endl;
    cout << "Δx = " << det_x << endl;
    cout << "Δy = " << det_y << endl;
    cout << "Δz = " << det_z << endl;
    
    // Проверяем, имеет ли система решение
    if (main_det == 0) {
        cout << "\nСистема не имеет единственного решения" << endl;
        if (det_x == 0 && det_y == 0 && det_z == 0) {
            cout << "Система имеет бесконечно много решений" << endl;
        } else {
            cout << "Система не имеет решений" << endl;
        }
    } else {
        // Находим решение
        double x = det_x / main_det;
        double y = det_y / main_det;
        double z = det_z / main_det;
        
        cout << "\nРешение:" << endl;
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        cout << "z = " << z << endl;
        
        // Проверка
        cout << "\nПроверка:" << endl;
        double eq1 = a1*x + b1*y + c1*z;
        double eq2 = a2*x + b2*y + c2*z;
        double eq3 = a3*x + b3*y + c3*z;
        
        cout << "Уравнение 1: " << a1 << "*" << x << " + " << b1 << "*" << y 
             << " + " << c1 << "*" << z << " = " << eq1 << " (должно быть " << d1 << ")" << endl;
        cout << "Уравнение 2: " << a2 << "*" << x << " + " << b2 << "*" << y 
             << " + " << c2 << "*" << z << " = " << eq2 << " (должно быть " << d2 << ")" << endl;
        cout << "Уравнение 3: " << a3 << "*" << x << " + " << b3 << "*" << y 
             << " + " << c3 << "*" << z << " = " << eq3 << " (должно быть " << d3 << ")" << endl;
    }
    
    return 0;
}
