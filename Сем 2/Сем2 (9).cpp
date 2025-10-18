#include<iostream>;
using namespace std;
int main() {
	setlocale(LC_ALL, "RU");
	int n;
	int sum = 0;
	cout << "Ââåäèòå ÷èñëî:";
	cin >> n;
	if (n < 1) {
		cout << "×èñëî äîëæíî áûòü áîëüøå 1";
	}
	else {
		for (int i = 1; i <= n; i++) {

			if (i % 2 == 0 || i % 5 == 0) {
				sum += i;
			}
		}

		cout << "Ñóììà ÷èñåë îò 1 äî " << n << ", äåëÿùèõñÿ íà 2 èëè íà 5:" << sum << endl;
	}
	return 0;
}
