#include <netdb.h>
#include <iostream>
#include <cstdlib>
#include <arpa/inet.h>
#include <strings.h>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "usage: " << argv[0] << " <hostname>" << endl;
        return 0;
    }
    struct hostent *hptr = gethostbyname(argv[1]);
    if (NULL == hptr)
    {
        cout << hstrerror(h_errno) << endl;
        exit(h_errno);
    }

    cout << "offical hostname: " << hptr->h_name << endl;
    for (char **p = hptr->h_aliases; *p != NULL; ++p)
    {
        cout << "alias: " << *p << endl;
    }
    for (char **p = hptr->h_addr_list; *p != NULL; ++p)
    {
        char str[INET_ADDRSTRLEN];
        bzero(str, sizeof(str));
        cout << "address: " << inet_ntop(hptr->h_addrtype, *p, str, sizeof(str)) << endl;
    }

    return 0;
}

