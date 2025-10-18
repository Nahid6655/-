#include <iostream>

using namespace std;

int main() {
    int n;
    
    cout << "Введите количество чисел n: ";
    cin >> n;
    
    int count = 0;
    
    cout << "Введите " << n << " натуральных чисел: ";
    for (int k = 1; k <= n; k++) {
        int Ak;
        cin >> Ak;
        
        if (Ak > 2 * k) {
            count++;
        }
    }
    
    cout << "Количество членов последовательности, удовлетворяющих условию Ak > 2k: " << count << endl;
    
    return 0;
}
