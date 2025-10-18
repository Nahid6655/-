#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");

    int n = 0, count = 0;
    
    cout << "Введите количество членов последовательности:\n";
    cin >> n;
    
    int* mas = new int[n];
    
    for (int i = 0; i < n; i++) {
        cout << "Введите элемент " << i + 1 << ": ";
        cin >> mas[i];
    }

    int max = -1; // Используем -1 как индикатор "не найдено"
    
    for (int i = 0; i < n; i++) {
        if (mas[i] % 2 == 0) {
            count++;
        } else {
            if (max == -1 || mas[i] > max) {
                max = mas[i];
            }
        }
    }

    cout << "В последовательности " << count << " четных чисел\n";
    
    if (max != -1) {
        cout << "Максимальное нечетное число последовательности: " << max;
    } else {
        cout << "В последовательности только четные числа";
    }

    delete[] mas;
    return 0;
}
