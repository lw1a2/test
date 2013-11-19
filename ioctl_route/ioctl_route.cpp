#include <sys/ioctl.h>
#include <iostream>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <net/route.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    int ret = 0;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock)
    {
        cout << "socket: " << strerror(errno) << endl;
        return errno;
    }

    struct rtentry rt;
    bzero(&rt, sizeof(rt));
    
    char dev[] = "eth1";
    rt.rt_dev = dev;
    
    rt.rt_dst.sa_family = AF_INET;
    if (inet_pton(AF_INET, "10.0.0.0", &((struct sockaddr_in*)&rt.rt_dst)->sin_addr) != 1)
    {
        cout << "inet_pton dst failed" << endl;
        return 1;
    }
    rt.rt_genmask.sa_family = AF_INET;
    if (inet_pton(AF_INET, "255.0.0.0", &((struct sockaddr_in*)&rt.rt_genmask)->sin_addr) != 1)
    {
        cout << "inet_pton dst failed" << endl;
        return 1;
    }


    ret = ioctl(sock, SIOCADDRT, &rt);
    if (-1 == ret)
    {
        cout << "ioctl: " << strerror(errno) << endl;
        return errno;
    }

    sleep(5);

    ret = ioctl(sock, SIOCDELRT, &rt);
    if (-1 == ret)
    {
        cout << "ioctl: " << strerror(errno) << endl;
        return errno;
    }

    return 0; 
}

