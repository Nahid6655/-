#include <iostream>
using namespace std;

int main() {
    const int n = 10;
    int arr[n];
    
    // Ввод
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Поиск индексов
    int minIdx = 0, maxIdx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[minIdx]) minIdx = i;
        if (arr[i] > arr[maxIdx]) maxIdx = i;
    }
    
    // Проверка условия и преобразование
    if (maxIdx == 1 && minIdx == 4) {
        for (int i = minIdx; i < n; i++) {
            arr[i] = arr[maxIdx];
        }
    }
    
    // Вывод
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    
    return 0;
}
