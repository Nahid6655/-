#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");
    
    const int N = 15;
    double mas[N];

    cout << "Введите " << N << " вещественных чисел:\n";
    for (int i = 0; i < N; i++) {
        cin >> mas[i];
    }

    int maxIndex = 0, minIndex = 0;

    for (int i = 1; i < N; i++) {
        if (mas[i] > mas[maxIndex]) maxIndex = i;
        if (mas[i] < mas[minIndex]) minIndex = i;
    }

    cout << "Минимальный: " << mas[minIndex] << " (поз. " << minIndex + 1 << ")" << endl;
    cout << "Максимальный: " << mas[maxIndex] << " (поз. " << maxIndex + 1 << ")" << endl;

    if (maxIndex < minIndex) {
        cout << "Произведение: " << mas[minIndex] * mas[maxIndex] << endl;
    }

    return 0;
}
