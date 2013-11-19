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

int sock_conn = -1;

void sig_urg(int)
{
    char buf[100];
    bzero(buf, sizeof(buf));
    int n = recv(sock_conn, buf, sizeof(buf), MSG_OOB); 
    if (-1 == n)
    {
        bzero(buf, sizeof(buf));
        strncpy(buf, "recv: ", strlen("recv: "));
        strncpy(buf + strlen(buf), strerror(errno), strlen(strerror(errno)));
        write(1, buf, strlen(buf));
        return;
    }
    else if (0 == n)
    {
        return;
    }

    write(1, "recv OOB: ", strlen("recv OOB: "));
    write(1, buf, n);
//  write(1, "\n", 1);
}

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

    sock_conn = accept(sock_listen, NULL, NULL);
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

    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sa.sa_handler = sig_urg;
    ret = sigaction(SIGURG, &sa, NULL);
    if (-1 == ret)
    {
        perror("sigaction");
        return errno;
    }

    ret = fcntl(sock_conn, F_SETOWN, getpid());
    if (-1 == ret)
    {
        perror("fcntl sock_conn"); 
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
            if (EINTR == errno)
            {
            }
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

