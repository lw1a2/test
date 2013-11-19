#include <netdb.h>
#include <iostream>
#include <errno.h>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main()
{
    struct servent* port = getservbyname("ftp", "tcp");
    if (NULL == port)
    {
        cout << "ERROR" << endl;
        return -1;
    }
    cout << "ftp with tcp: " << ntohs(port->s_port) << endl;

    struct servent* name = getservbyport(htons(21), "tcp");
    if (NULL == name)
    {
        cout << "ERROR" << endl;
        return -1;
    }
    cout << "port 21 with tcp: " << name->s_name << endl;

    return 0;
}

