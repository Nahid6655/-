#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL, "RU");

    int a;
    cout << "Âåäèòå äëèíó â ñàíòèìåòðàõ:" << endl;
    cin >> a;
    cout << a / 100 << " ì " << a % 100 << " ñì " << endl;

    return 0;
}
