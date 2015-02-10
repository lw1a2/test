#include <string.h>

void f()
{
    int a[10];
    memset(a, 0, 100000);
}

int main()
{
    f();
    return 0;
}