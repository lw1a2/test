#include <iostream>

using namespace std;

class A
{
public:
	A(int i)
	{
		cout << "A()" << endl;
	}

	~A()
	{
		cout << "~A()" << endl;
	}
};

A f()
{
	A a(1);
	return a;
}

int main()
{
	A a2 = f();
	return 0;
}

