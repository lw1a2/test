#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

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
    ret = setsockopt(sock_listen, SOL_SOCKET, SO_OOBINLINE, &opt, sizeof(opt));
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
    inet_pton(AF_INET, "172.173.1.1", &serv.sin_addr);
    serv.sin_port = htons(8888);

    ret = bind(sock_listen, (struct sockaddr *)&serv, sizeof(serv));
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

    int sock_conn = accept(sock_listen, NULL, NULL);
    if (-1 == sock_conn)
    {
        if (EINTR == errno)
        {}
        else
        {
            perror("accept");
            return errno;
        }
    }

    sleep(1);

    char buf[10240];
    int i = 0;

    while (1)
    {
        bzero(buf, sizeof(buf));
        if (sockatmark(sock_conn)) 
        {
            cout << "at OOB mark" << endl;
        }

        int n = read(sock_conn, buf, sizeof(buf));
        if (-1 == n)
        {
            if (EINTR == errno)
            {}
            else
            {
                perror("read");
                return errno;
            }
        }
        else if (0 == n)
        {
            return 0;
        }

        printf("%s\n", buf);
    }

    return 0;
}

