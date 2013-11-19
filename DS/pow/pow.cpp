#include <iostream>

using namespace std;

long pow(long x, int n)
{
    if (n == 0)
    {
        return 1;
    }
    else if (n % 2 == 0)
    {
        return pow(x * x, n / 2);
    }
    else
    {
        return pow(x * x, (n - 1) / 2) * x;
    }
}

long pow2(long x, int n)
{
    long r = x;
    long s = 1;
    while (n)
    {
        if (n & 1)
        {
            s *= r;
        }
        r *= r;
        n >>= 1;
    }
    return s;
}

int main()
{
    cout << pow(10, 5) << endl;
    cout << pow2(10, 5) << endl;
    cout << pow(10, 8) << endl;
    cout << pow2(10, 8) << endl;
    return 0;
}

