#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");

    const int n = 15;
    float mas[n];

    for (int i = 0; i < n; i++) {
        cout << "Введите число " << i + 1 << ": ";
        cin >> mas[i];
    }

    cout << "\nИсходный массив:\n";
    for (int i = 0; i < n; i++) {
        cout << mas[i] << " ";
    }

    int maxIndex = 0, minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (mas[i] > mas[maxIndex]) maxIndex = i;
        if (mas[i] < mas[minIndex]) minIndex = i;
    }

    cout << "\n\nМаксимальный элемент: " << mas[maxIndex] 
         << " (позиция " << maxIndex + 1 << ")";
    cout << "\nМинимальный элемент: " << mas[minIndex] 
         << " (позиция " << minIndex + 1 << ")";

    if (maxIndex == 0 && minIndex == 1) {
        cout << "\n\nУсловие выполнено! Умножаем все элементы на 0.5";
        for (int i = 0; i < n; i++) {
            mas[i] *= 0.5f;
        }
    } else {
        cout << "\n\nУсловие не выполнено!";
        cout << "\nТребуется: максимум на 1-й позиции, минимум на 2-й";
    }

    cout << "\n\nИтоговый массив:\n";
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(2) << mas[i] << " ";
    }
    cout << endl;

    return 0;
}
