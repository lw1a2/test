#include <iostream>
#include <strings.h>
#include <cstring>

using namespace std;

void* my_memcpy(void *dest, const void *src, size_t count)
{
    char *pDest = static_cast<char*>(dest);
    const char *pSrc = static_cast<const char*>(src);

    if (pDest > pSrc && pDest < pSrc + count)
    {
        for (size_t i = count; i > 0; --i)
        {
            pDest[i - 1] = pSrc[i - 1];
        }
    }
    else
    {
        for (size_t i = 0; i < count; ++i)
        {
            pDest[i] = pSrc[i];
        }
    }

    return pDest;
}

int main()
{
    char c1[128];
    bzero(c1, sizeof(c1));
    char c2[128];
    bzero(c2, sizeof(c2));
    strcpy(c1, "ABC");
    int n = strlen(c1);
    my_memcpy(c2, c1, n);
    cout << c2 << endl;

    my_memcpy(c1 + 1, c1, n);
    cout << c1 + 1 << endl;

    return 0;
}

