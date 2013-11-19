#include <iostream>
#include "String.h"

using namespace std;

void testString()
{
    String s = "abc";
    String s2 = s;
    String s3 = "123";
    s3 = s2;
    cout << s3[1] << endl;
    s3[1] = 'd';
}

int main()
{
    testString();
    return 0;
}

