#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, "RU");
	float a;
	cout << "������� ����������� ������� �� �����:";
		cin >> a;
		if (a < 0)
		{
			cout << "�������� ������ ������";
		}
		else if (a >= 0 && a <= 10)
		{
			cout << "�������� ������ ������";
		}
		else if (a >= 11 && a <= 20)
		{
			cout << "�������� ������ ������";
		}
		else if (a > 20)
		{
			cout << "�������� ������ ������";
		}
	return 0;
}
//int main() {
//	setlocale(LC_ALL, "RU");
//	int stops;
//	const int price = 5;
//	cout << "������� ���������� ���������:";
//		cin >> stops;
//		int t = 0;
//		for (int i = 0;i < stops;i++) 
//		{
//			t += price;
//		}
//		cout << "�����������������:" << t << endl;
//		return 0;
//}

