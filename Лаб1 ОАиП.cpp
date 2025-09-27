#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RU");
	const int size = 10;
	int a[size];
	cout << "Ââåäèòå 10 öåëûõ ÷èñåë:" << endl;
	for (int i = 0; i < size; i++) {
		cout << "Ââåäèòå ÷èñëî:" << i << ":";
		cin >> a[i];
	}
	for (int i = 0; i < size; i++) {
		cout << a[i] << " ";
	}
	int sum = 0;
	int max = 0;
	for (int i = 0;i < size;i++) {
		sum += a[i];
		if (max < a[i])
			max = a[i];
	}
	cout << "Ñóììà âñåõ ýëåìåíòîâ:" << sum << endl;
	cout << "Ìàêñèìàëüíûé ýëåìåíò:" << max << endl;
		for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
				if (a[j] < a[j + 1]) {
					int temp = a[j];
					a[j] = a[j + 1];
					a[j + 1] = temp;
				}
			}
		}
	}
	for (int i = 0; i < size; i++) {
		cout << a[i] << " ";
	}
	return 0;
}

