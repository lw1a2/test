#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main()
{
    int ret = 0;
    int fd = -1;
    void* p = NULL;
    const char * const name = "/DnsCache";

    fd = shm_open(name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    cout << fd << endl;
    if (-1 == fd)
    {
        perror(strerror(errno));
        exit(errno);
    }

    ret = ftruncate(fd, 1024);

    p = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ret = close(fd);
    if ((long)p == -1)
    {
        perror(strerror(errno));
        exit(errno);
    }

    cout << p << endl;

    strncpy((char*)p, "aaa", sizeof("aaa"));

    return 0;
}

