#include <iostream>

using namespace std;

void f3()
{
//  int *p = 0;
//  *p = 0;
    int i;
    int *p = &i;
    for (int j = 0; j < 20; ++j)
    {
        cout << p << endl;
        *(++p) = 0x28;
    }
}

void f2()
{
    f3();
}

void f1()
{
    f2();
}
 
int main()
{
   f1();
   return 0;
}

