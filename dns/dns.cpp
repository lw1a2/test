#include <iostream>
#include <netdb.h>
#include <strings.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

using namespace std;

int main()
{
    struct hostent * host = gethostbyname("www.baidu.com");
    if (!host)
    {
        cout << "gethostbyname failed: " << hstrerror(h_errno) << endl;
        return 1;
    }

    cout << "canonical name: " << host->h_name << endl;
    cout << "type: " << host->h_addrtype << endl;
    cout << "length: " << host->h_length << endl;
    for (char ** pp = host->h_aliases; *pp != NULL; ++pp)
    {
        cout << "alias: " << *pp << endl;
    }
    char buf[INET_ADDRSTRLEN];
    bzero(buf, sizeof(buf));
    for (char ** pp = host->h_addr_list; *pp != NULL; ++pp)
    {
        if (inet_ntop(AF_INET, *pp, buf, sizeof(buf)))
        {
            cout << "address: " << buf << endl;
        }
    }

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, "172.173.1.1", &addr.sin_addr) != 1)
    {
        cout << "inet_pton failed: " << strerror(errno) << endl;
    }
        
    struct hostent * host2 = gethostbyaddr(&addr.sin_addr, sizeof(addr), AF_INET);
    if (!host2)
    {
        cout << "gethostbyname failed: " << hstrerror(h_errno) << endl;
        return 1;
    }
    cout << "canonical name: " << host2->h_name << endl;

    return 0;
}

