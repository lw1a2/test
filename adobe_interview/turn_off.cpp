#include <iostream>

using namespace std;

int f(int n)
{
	int i = 0;
	while (!(n & 1))
	{
		n >>= 1;
		i++;
	}
	n--;
	while (i--)	n <<= 1;
	return n;
}

int main()
{
	cout << f(14) << endl;

	return 0;
}
