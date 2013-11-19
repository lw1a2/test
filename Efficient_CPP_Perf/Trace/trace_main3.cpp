#include <iostream>
#include <sys/time.h>
using namespace std;

class Trace
{
public:
	~Trace()// Version 3
	{
		if (TraceIsActive)
		{
			cout << "Exit function " << *theFunctionName << endl;
			delete theFunctionName;
		}

	}

	Trace(const char *name) : theFunctionName(0)// Version 3
	{
		if (TraceIsActive)
		{
			cout << "Enter function" << name << endl;
			theFunctionName = new string(name);
		}
	}


	void debug(const char *msg)// Version 2
	{
		if (TraceIsActive)
		{
			cout << msg << endl;
		}
	}

	static bool TraceIsActive;
private:
	string *theFunctionName; // Version 3
};

bool Trace::TraceIsActive;

//int addOne(int x)     // Version 0
//{
//    return x+1;
//}

int addOne(int x)	  // Version 2. Forget the string object.
// Use a char pointer instead.
{
	char  *name = "addOne";
	Trace t(name);

	return x+1;
}

int main()
{
	Trace::TraceIsActive = false;//Turn tracing off
	struct timeval tv, tv2;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	tv2 = tv;
	gettimeofday(&tv, NULL);	// Start timing

	for (int i =0; i < 1000000; i++)
	{
		addOne(i);
	}

	gettimeofday(&tv2, NULL);	 // Stop timing
	// ...

	cout << (tv2.tv_sec - tv.tv_sec) * 1000000 + tv2.tv_usec - tv.tv_usec << endl;

	return 0;
}


