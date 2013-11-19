#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <net/if_arp.h>
#include <iostream>
#include <sys/ioctl.h>
#include <stdio.h>

using namespace std;

int main()
{
    int ret = 0;
    struct arpreq arp;
    bzero(&arp, sizeof(arp));

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, "172.173.1.32", &addr.sin_addr) != 1)
    {
        cout << "inet_pton failed" << endl;
        return 1;
    }

    memcpy(&arp.arp_pa, &addr, sizeof(addr));

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sock)
    {
        cout << "socket: " << strerror(errno) << endl;
        return errno;
    }

    strncpy(arp.arp_dev, "eth0", strlen("eth0"));
    
    ret = ioctl(sock, SIOCGARP, &arp);
    if (-1 == ret)
    {
        cout << "ioctl: " << strerror(errno) << endl;
        return errno;
    }

    unsigned char * ptr = (unsigned char *)&arp.arp_ha.sa_data[0];
    printf("%x:%x:%x:%x:%x:%x\n", *ptr, *(ptr + 1),
           *(ptr + 2), *(ptr + 3), *(ptr + 4), *(ptr + 5));

    return 0; 
}

