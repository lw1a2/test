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
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sock)
    {
        perror("socket");
        return errno;
    }

    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    inet_pton(AF_INET, "10.1.1.133", &serv.sin_addr);
    serv.sin_port = htons(8888);

    ret = connect(sock, (struct sockaddr*)&serv, sizeof(serv));
    if (-1 == ret)
    {
        perror("connect");
        return errno;
    }

    char buf[10240];

    while (1)
    {
        bzero(buf, sizeof(buf));
        int n = read(STDIN_FILENO, buf, sizeof(buf));
        if (-1 == n)
        {
            perror("read from STDIN_FILENO");
            return errno;
        }
        else if (0 == n)
        {
            break;
        }

        //n = sendto(sock, buf, n, 0, NULL, 0);
        n = write(sock, buf, n);
        if (-1 == n)
        {
            //perror("sendto");
            perror("write");
            return errno;
        }

        bzero(buf, sizeof(buf));
        //n = recvfrom(sock, buf, sizeof(buf), 0, NULL, NULL);
        n = read(sock, buf, sizeof(buf));
        if (-1 == n)
        {
            //perror("recvfrom serv");
            perror("read");
            return errno;
        }
        else if (0 == n)
        {
            break;
        }

        printf("echo: %s", buf);
    }

    return 0;
}

