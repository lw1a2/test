#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/*
    Test <TCP IP Illustrated Volume 1 The Protocols (2E)> P622.
    It's a client, you can use nc -l 6666 as a server.
    nc -l 
*/

int main()
{
    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(6666);
    if (inet_pton(AF_INET, "172.22.15.230", &serv.sin_addr) != 1) {
        printf("inet_pton server 172.22.15.230 failed\n");
        return 1;
    }

    struct sockaddr_in cli;
    bzero(&cli, sizeof(cli));
    cli.sin_family = AF_INET;
    cli.sin_port = htons(32840);
    cli.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = 0;
    int sock = -1;
    int on = 1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock) {
        perror("socket");
        return errno;
    }
    ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (-1 == ret) {
        perror("setsockopt");
        return errno;
    }
    ret = bind(sock, (struct sockaddr*)&cli, sizeof(cli));
    if (-1 == ret)
    {
        perror("bind client");
        return errno;
    }
    ret = connect(sock, (sockaddr *)&serv, sizeof(serv));
    if (-1 == ret) {
        perror("connect 6666");
        return errno;
    }

    sleep(9999);

    return 0;
}

