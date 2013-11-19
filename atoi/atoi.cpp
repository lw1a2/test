#include <iostream>
#include <cstdlib>

using namespace std;

int my_atoi(const char *c)
{
    if (!c)
    {
        return 0;
    }
    const char * p = c;
    bool negative = false;
    if ('-' == *p)
    {
        negative = true;
        ++p;
    }

    int res = 0;
    while (*p)
    {
        if (*p <= '9' && *p >= '0')
        {
            res = res * 10 + *p - '0';
            ++p;
        }
        else
        {
            return res;
        }
    }

    if (negative)
    {
        return 0 - res;
    }

    return res;
}



int main()
{
    cout << atoi("133") << endl;
    cout << atoi("-133") << endl;
    cout << atoi("a") << endl;
//  cout << atoi(NULL) << endl;

    cout << my_atoi("133") << endl;
    cout << my_atoi("-133") << endl;
    cout << my_atoi("a") << endl;
    cout << my_atoi(NULL) << endl;

    return 0;
}
