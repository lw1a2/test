#include <iostream>

using  namespace std;

bool DivideBy3(int n)
{
	int s = 0;
	if (n < 0) n = -n;
	
	while (n > 0)
	{
		s = n & 1;
		n >>= 1;
		n = n - s;
	}
	
	return (n == 0);
}

int main()
{
	cout << DivideBy3(6) << endl;
	cout << DivideBy3(3) << endl;
	cout << DivideBy3(0) << endl;
	cout << DivideBy3(2) << endl;
	cout << DivideBy3(10) << endl;
	cout << DivideBy3(111) << endl;
	cout << DivideBy3(18) << endl;
	cout << DivideBy3(131) << endl;
	return 0;
}

