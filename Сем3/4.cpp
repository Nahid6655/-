#include <iostream>
using namespace std;

int main() {
    const int n = 15;
    double arr[n];
    
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    int minIndex = 0, maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[minIndex]) minIndex = i;
        if (arr[i] > arr[maxIndex]) maxIndex = i;
    }
    
    if (maxIndex < minIndex) {
        double product = arr[minIndex] * arr[maxIndex];
        cout << "Произведение: " << product << endl;
    } else {
        cout << "Условие не выполнено" << endl;
    }
    
    return 0;
}
