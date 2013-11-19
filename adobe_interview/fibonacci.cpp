#include <iostream>

using namespace std;

int f(int n)
{
	if (n <= 2) return 1;
	else return f(n - 1) + f(n - 2);
}

int f2(int n)
{
	if (n <= 2) return 1;
	int a = 1, b = 1, c = 0;
	for (int i = 3; i <= n; i++) 
	{
        c = a + b;
        a = b;
        b = c;
    }
	
    return c;
}

int main()
{
	for (int i = 1; i < 10; ++i)
	{
		cout << f(i) << endl;
		cout << f2(i) << endl;
		cout << endl;
	}
	
	return 0;
}

