#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, "RU");
	float a;
	cout << "Введите температуру воздуха на улице:";
		cin >> a;
		if (a < 0)
		{
			cout << "Наденьте зимнюю одежду";
		}
		else if (a >= 0 && a <= 10)
		{
			cout << "Наденьте теплую одежду";
		}
		else if (a >= 11 && a <= 20)
		{
			cout << "Наденьте легкую одежду";
		}
		else if (a > 20)
		{
			cout << "Наденьте летнюю одежду";
		}
	return 0;
}
//int main() {
//	setlocale(LC_ALL, "RU");
//	int stops;
//	const int price = 5;
//	cout << "Введите количество остановок:";
//		cin >> stops;
//		int t = 0;
//		for (int i = 0;i < stops;i++) 
//		{
//			t += price;
//		}
//		cout << "Стоимостьмпроезда:" << t << endl;
//		return 0;
//}

