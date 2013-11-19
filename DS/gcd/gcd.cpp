#include <iostream>

using namespace std;

long gcd(long m, long n)
{
    if (n == 0)
    {
        return m;
    }

    return gcd(n, m % n);
}

long gcd2(long m, long n)
{
    while (n != 0)
    {
        int tmp = m;
        m = n;
        n = tmp % n;
    }

    return m;
}

int main()
{
    cout << "1989, 1590: " << gcd(1989, 1590) << endl;
    cout << "1989, 1590: " << gcd2(1989, 1590) << endl;

    return 0;
}

