#include <iostream>

using namespace std;

int j = 0;

void f()
{
	j = 1;
}

int main()
{
	f();

	for (int i = 0; i < 10000; ++i)
	{
		cout << i << endl;
		if (i == 8888)
		{
			j = i;
		}
	}

	return 0;
}

	
