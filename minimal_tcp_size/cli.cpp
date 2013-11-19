#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>

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
    inet_pton(AF_INET, "1.1.1.2", &cli.sin_addr);
    ret = bind(sock, (struct sockaddr*)&cli, sizeof(cli));
    if (-1 == ret)
    {
        perror("bind");
        return errno;
    }

    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    inet_pton(AF_INET, "2.1.1.2", &serv.sin_addr);
    serv.sin_port = htons(8888);

    ret = connect(sock, (struct sockaddr*)&serv, sizeof(serv));
    if (-1 == ret)
    {
        perror("connect");
        return errno;
    }

    const char* str = "1";
    char buf[10240];

    int i = 0;
    while (1)
    {
        bzero(buf, sizeof(buf));
        sprintf(buf, "%d", i);
        int n = write(sock, buf, 5000);
        if (-1 == n)
        {
            perror("write");
            return errno;
        }

        sleep(1);
        printf("%d\n", i++);
    }

    return 0;
}

