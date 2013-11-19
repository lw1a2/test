#include <iostream>
#include <sys/time.h>

using namespace std;

class Rational {
public:
    Rational (int a = 0, int b = 1 ) : n(a), d(b) {}
private:
    int n;   // Numerator
    int d;   // Denominator
};

int main()
{
    Rational *array[1000];
    
    // Start timing here
	struct timeval tv, tv2;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	tv2 = tv;
	gettimeofday(&tv, NULL);

    for (int j = 0; j < 500; j++)   {
         for (int i = 0; i < 1000; i++)   {
              array[i] = new Rational(i);
              }
         for (int i = 0; i < 1000; i++)   {
              delete array[i];
              }
         }

    // Stop timing here
	gettimeofday(&tv2, NULL);

	cout << (tv2.tv_sec - tv.tv_sec) * 1000000 + tv2.tv_usec - tv.tv_usec << endl;

    return 0;
}


