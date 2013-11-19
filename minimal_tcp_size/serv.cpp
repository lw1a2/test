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
    int sock_listen = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock_listen)
    {
        perror("socket");
        return errno;
    }

    int opt = 1;
    ret = setsockopt(sock_listen, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));
    if (-1 == ret)
    {
        perror("setsockopt");
        return errno;
    }

    opt = 1;
    ret = setsockopt(sock_listen, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (-1 == ret)
    {
        perror("setsockopt");
        return errno;
    }

    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    inet_pton(AF_INET, "1.1.1.1", &serv.sin_addr);
    //serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(8888);

    ret = bind(sock_listen, (struct sockaddr*)&serv, sizeof(serv));
    if (-1 == ret)
    {
        perror("bind");
        return errno;
    }

    ret = listen(sock_listen, 5);
    if (-1 == ret)
    {
        perror("listen");
        return errno;
    }

    while (1)
    {
        int sock_conn = accept(sock_listen, NULL, NULL);
        if (-1 == sock_conn)
        {
            perror("accept");
            return errno;
        }

        char buf[10240];
        int i = 0;
        while (1)
        {
            bzero(buf, sizeof(buf));
            int n = read(sock_conn, buf, sizeof(buf));
            if (-1 == n)
            {
                perror("read");
                break;
            } else if (0 == n)
            {
                break;
            }

            if (strlen(buf))
            {
                printf("%s\n", buf);
            }
        }
        close(sock_conn);
    }

    return 0;
}

