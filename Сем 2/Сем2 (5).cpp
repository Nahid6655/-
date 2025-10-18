#include<iostream>;
using namespace std;
int main() {
	setlocale(LC_ALL, "RU");
	int a;
	cout << "Ââåäèòå ÷èñëî:";
	cin >> a;
    if (a % 5 == 0 && a % 3 == 0) {
		cout << "×èñëî äåëèòñÿ íà 3 è íà 5";
	}
	else if (a % 5 == 0) {
		cout << "×èñëî äåëèòñÿ íà 5";
	}
	else if (a % 3 == 0) {
		cout << "×èñëî äåëèòñÿ íà 3";
	}
	
	else {
		cout << "×ìñëî íå äåëèòñÿ íè íà 3, íè íà 5";
	}
	return 0;
}
