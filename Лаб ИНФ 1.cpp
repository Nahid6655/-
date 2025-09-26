#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, "RU");
	float a;
	cout << "Ââåäèòå òåìïåðàòóðó âîçäóõà íà óëèöå:";
		cin >> a;
		if (a < 0)
		{
			cout << "Íàäåíüòå çèìíþþ îäåæäó";
		}
		else if (a >= 0 && a <= 10)
		{
			cout << "Íàäåíüòå òåïëóþ îäåæäó";
		}
		else if (a >= 11 && a <= 20)
		{
			cout << "Íàäåíüòå ëåãêóþ îäåæäó";
		}
		else if (a > 20)
		{
			cout << "Íàäåíüòå ëåòíþþ îäåæäó";
		}
	return 0;
}
//int main() {
//	setlocale(LC_ALL, "RU");
//	int stops;
//	const int price = 5;
//	cout << "Ââåäèòå êîëè÷åñòâî îñòàíîâîê:";
//		cin >> stops;
//		int t = 0;
//		for (int i = 0;i < stops;i++) 
//		{
//			t += price;
//		}
//		cout << "Ñòîèìîñòüìïðîåçäà:" << t << endl;
//		return 0;
//}

