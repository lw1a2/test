#include <sys/socket.h>
#include <iostream>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    int ret = 0;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sock)
    {
        cout << "socket: " << strerror(errno) << endl;
        return errno;
    }

    struct ifconf ifc;
    bzero(&ifc, sizeof(ifc));
    ifc.ifc_len = 100 * sizeof(struct ifreq);
    ifc.ifc_buf = new char[ifc.ifc_len];

    ret = ioctl(sock, SIOCGIFCONF, &ifc);
    if (-1 == ret)
    {
        cout << "ioctl SIOCGIFCONF: " << strerror(errno) << endl;
        return errno;
    }

    struct ifreq *p = NULL;
    for (int i = 0; i * sizeof(struct ifreq) < ifc.ifc_len; i++)
    {
        p = ifc.ifc_req + i;
        if (p)
        {
            if (AF_INET == p->ifr_addr.sa_family)
            {
                char buf[INET_ADDRSTRLEN];
                bzero(buf, sizeof(buf));
                cout << p->ifr_name << ": "
                    << inet_ntop(AF_INET, &((struct sockaddr_in *)&p->ifr_addr)->sin_addr, buf, sizeof(struct sockaddr_in));
            }
            else if (AF_INET6 == p->ifr_addr.sa_family)
            {
                char buf[INET6_ADDRSTRLEN];
                bzero(buf, sizeof(buf));
                cout << p->ifr_name << ": "
                    << inet_ntop(AF_INET6, &((struct sockaddr_in6 *)&p->ifr_addr)->sin6_addr, buf, sizeof(struct sockaddr_in6));
            }
            else
            {
                cout << "Error sa_family: " << p->ifr_addr.sa_family << endl;
                return 1;
            }
            struct ifreq ifstatus = *p;
            ret = ioctl(sock, SIOCGIFFLAGS, &ifstatus);
            if (-1 == ret)
            {
                cout << "ioctl SIOCGIFFLAGS: " << strerror(errno) << endl;
                return errno;
            }
            if (ifstatus.ifr_flags & IFF_UP)
            {
                cout << " UP "; 
            }
            else
            {
                cout << " DOWN "; 
            }

            cout << endl;
        }
    }
    return 0;
}

