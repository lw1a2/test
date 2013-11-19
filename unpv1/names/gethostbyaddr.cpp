#include <netdb.h>
#include <iostream>
#include <cstdlib>
#include <arpa/inet.h>
#include <strings.h>
#include <cstdio>
#include <errno.h>
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "usage: " << argv[0] << " IPaddress" << endl;
        return 0;
    }

    struct sockaddr_in addr;
    int ret = inet_pton(AF_INET, argv[1], &addr.sin_addr);
    if (ret != 1)
    {
        perror("inet_pton");
        exit(errno);
    }
    struct hostent *name = gethostbyaddr(&addr.sin_addr, sizeof(addr.sin_addr), AF_INET);
    if (NULL == name)
    {
        cout << "gethostbyaddr: " << hstrerror(h_errno) << endl;
        exit(h_errno);
    }

    cout << name->h_name << endl;

    return 0;
}
