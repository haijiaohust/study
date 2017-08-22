#include <iostream>
using namespace std;
int gcd(int a, int b)
{
    int c = a%b;
    while(c)
    {
        a = b;
        b = c;
        c = a % b;
    }
    return b;
}
int main()
{
    cout << gcd(10, 15) << endl;
    return 0;
}
