#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <iostream>
#include <sys/select.h>

using namespace std;

int main()
{
    int ret = 0;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock)
    {
        perror("socket");
        return errno;
    }

    int opt = 1;
    ret = setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));
    if (-1 == ret)
    {
        perror("setsockopt");
        return errno;
    }

    struct sockaddr_in cli;
    bzero(&cli, sizeof(cli));
    cli.sin_family = AF_INET;
    inet_pton(AF_INET, "172.173.1.107", &cli.sin_addr);

    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    inet_pton(AF_INET, "172.173.1.105", &serv.sin_addr);
    serv.sin_port = htons(8888);

    ret = connect(sock, (struct sockaddr*)&serv, sizeof(serv));
    if (-1 == ret)
    {
        perror("connect");
        return errno;
    }

    char buf[10240];
    bool input_over = false;

    ret = shutdown(sock, SHUT_RD);
    if (-1 == ret)
    {
        perror("shutdown");
        return errno;
    }
    
    return 0;
}

