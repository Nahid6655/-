#include <iostream>
using namespace std;
int main()
{
    setlocale(LC_ALL, "RU");

    int a;
    cout << "Ведите длину в сантиметрах:" << endl;
    cin >> a;
    cout << a / 100 << " м " << a % 100 << " см " << endl;

    return 0;
}
