#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL, "RU");

    int a;
    cout << "������ ����� � �����������:" << endl;
    cin >> a;
    cout << a / 100 << " � " << a % 100 << " �� " << endl;

    return 0;
}
