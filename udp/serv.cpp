#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main()
{
    int ret = 0;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sock)
    {
        perror("socket");
        return errno;
    }

    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8888);
//  inet_pton(AF_INET, "172.173.1.1", &serv.sin_addr);
//  serv.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr);

    ret = bind(sock, (sockaddr*)&serv, sizeof(serv));
    if (-1 == ret)
    {
        perror("bind");
        return errno;
    }

    struct sockaddr_in cli;
    bzero(&cli, sizeof(cli));
    socklen_t len = sizeof(cli);
    char buf[10240];

    while (1)
    {
        bzero(buf, sizeof(buf));
        int n = recvfrom(sock, buf, sizeof(buf), 0, (sockaddr*)&cli, &len);
        if (-1 == n)
        {
            perror("recvfrom");
            return errno;
        }

        char addr_buf[INET_ADDRSTRLEN];
        bzero(addr_buf, sizeof(addr_buf));
        if (inet_ntop(AF_INET, &cli.sin_addr, addr_buf, sizeof(addr_buf)))
        {
            printf("%s.%d: ", addr_buf, ntohs(cli.sin_port));
        }
        printf("%s\n", buf);
//
//      //echo
//      n = sendto(sock, buf, n, 0, (sockaddr*)&cli, len);
//      if (-1 == n)
//      {
//          perror("sendto");
//          return errno;
//      }
    }

    return 0;
}

