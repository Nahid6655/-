#include <iostream>
using namespace std;

int main() {
    const int n = 15;
    double arr[n];
    
    cout << "Введите " << n << " вещественных чисел:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int minIndex = 0, maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[minIndex]) minIndex = i;
        if (arr[i] > arr[maxIndex]) maxIndex = i;
    }
    
    swap(arr[0], arr[minIndex]);
    
    if (maxIndex == 0) maxIndex = minIndex;
    
    swap(arr[n - 1], arr[maxIndex]);
    
    cout << "Результат:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    
    return 0;
}
