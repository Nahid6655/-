#include<iostream>;
using namespace std;
int main() {
	setlocale(LC_ALL, "RU");
	int a;
	cout << "Ââåäèòå ÷èñëî:";
	cin >> a;
	if (a % 2==0) {
		cout << "×èñëî ÷åòíîå";
	}
	else {
		cout << "×èñëî íå÷åòíîå";
	}
	return 0;
