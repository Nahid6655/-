#include<iostream>;
using namespace std;
int main() {
	setlocale(LC_ALL, "RU");
	int n = 0;
	cout << "Ââåäèòå ÷èñëî:";
	cin >> n;
	if (n < 1) {
		cout << "×èñëî äîëæíî áûòü áîëüøå 1";
	}

	for (int i = 1; i <= n; i++) {
		cout << i << "*" << i << "=" << i * i << endl;
	}
	return 0;
}
