#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    
    double centr[3][2];

    cout << "Введите координаты вершин треугольника" << endl;

    for (int j = 0; j < 3; j++) {
        cout << "Вершина " << j + 1 << " (x, y): ";
        cin >> centr[j][0] >> centr[j][1];
    }

    double x4 = centr[0][0], y4 = centr[0][1];
    double x5 = centr[1][0], y5 = centr[1][1];
    double x6 = centr[2][0], y6 = centr[2][1];

    // Вычисление центра масс треугольника
    // Формула: ( (x1+x2+x3)/3 , (y1+y2+y3)/3 )
    double c_x = (x4 + x5 + x6) / 3;
    double c_y = (y4 + y5 + y6) / 3;

    cout << fixed << setprecision(2);
    cout << "Координаты центра масс: (" << c_x << ", " << c_y << ")" << endl;

    return 0;
}
