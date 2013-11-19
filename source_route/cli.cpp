#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main()
{
    int ret = 0;

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sock)
    {
        perror("socket");
        return errno;
    }

    char arg[40];
    bzero(arg, sizeof(arg));
    char *p = arg;
    *p++ = IPOPT_NOP;   //NOP
    *p++ = IPOPT_SSRR;  //type
    *p++ = 7;           //len
    *p++ = 4;           //first address
    struct sockaddr_in inter_addr;
    bzero(&inter_addr, sizeof(inter_addr));
    inter_addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, "172.173.1.2", &inter_addr.sin_addr) != 1)
    {
        printf("inet_pton inter_addr failed\n");
        return 1;
    }
    memcpy(p, &inter_addr.sin_addr, sizeof(inter_addr.sin_addr));

    ret = setsockopt(sock, IPPROTO_IP, IP_OPTIONS, arg, 8);
    if (-1 == ret)
    {
        perror("setsockopt");
        return errno;
    }

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(58888);
    if (inet_pton(AF_INET, "172.173.1.102", &addr.sin_addr) != 1)
    {
        printf("inet_pton addr failed\n");
        return 1;
    }

    int n = sendto(sock, "123", strlen("123"), 0, (struct sockaddr *)&addr, sizeof(addr));
    if (-1 == n)
    {
        perror("sendto");
        return errno;
    }

    return 0;
}

