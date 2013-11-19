#include <sys/types.h>
#include <ifaddrs.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    int ret = 0;

    struct ifaddrs* ifs;
    ret = getifaddrs(&ifs);
    if (-1 == ret)
    {
        cout << "getifaddrs: " << strerror(errno) << endl;
        return errno;
    }

    struct ifaddrs* p = ifs;
    char buf[INET6_ADDRSTRLEN];
    bzero(buf, sizeof(buf));
    while (p)
    {
        if (AF_INET == p->ifa_addr->sa_family || AF_INET6 == p->ifa_addr->sa_family)
        {
            cout << p->ifa_name << ": " 
                << inet_ntop(p->ifa_addr->sa_family, &((struct sockaddr_in*)p->ifa_addr)->sin_addr, buf, sizeof(buf)) << endl;
        }
        p = p->ifa_next;
    }
    freeifaddrs(ifs); 
    return 0;
}
