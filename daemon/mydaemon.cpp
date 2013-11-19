#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <iostream>

using namespace std;

int main()
{
    int ret = 0;
    
    ret = daemon(0, 0);
    if (-1 == ret)
    {
        cout << strerror(errno) << endl;
        return errno;
    }

    pause();

    return 0;
}

