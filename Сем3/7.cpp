#include <iostream>
using namespace std;

int main() {
    const int n = 15;
    int arr[n];
    
    // Ввод массива
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Поиск min и max
    int minIndex = 0, maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[minIndex]) minIndex = i;
        if (arr[i] > arr[maxIndex]) maxIndex = i;
    }
    
    // Проверка условия и обнуление
    if (arr[minIndex] == 0 || arr[maxIndex] == 0) {
        for (int i = 0; i < minIndex; i++) {
            arr[i] = 0;
        }
    }
    
    // Вывод результата
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    
    return 0;
}
