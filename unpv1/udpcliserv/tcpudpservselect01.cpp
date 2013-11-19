#include <sys/select.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include <strings.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <algorithm>

typedef struct sockaddr SA;

#define MAXLINE 4096

void sig_chld(int signo)
{
    pid_t pid = 0;
    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0);
}

int main()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listenfd)
    {
        perror("tcp socket");
        exit(errno);
    }

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8888);

    const int on = 1;
    int ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (-1 == ret)
    {
        perror("setsockopt");
        exit(errno);
    }

    ret = bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
    if (-1 == ret)
    {
        perror("tcp bind");
        exit(errno);
    }

    ret = listen(listenfd, 5);
    if (-1 == ret)
    {
        perror("listen");
        exit(errno);
    }

    int udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == udpfd)
    {
        perror("udp socket");
        exit(errno);
    }

    ret = bind(udpfd, (SA*)&servaddr, sizeof(servaddr));
    if (-1 == ret)
    {
        perror("udp bind");
        exit(errno);
    }

    struct sigaction sa;
    sa.sa_flags = 0;
#ifdef SA_RESTART
    sa.sa_flags |= SA_RESTART;
#endif
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = sig_chld;
    ret = sigaction(SIGCHLD, &sa, NULL);
    if (-1 == ret)
    {
        perror("sigaction");
        exit(errno);
    }

    fd_set rset;
    FD_ZERO(&rset);
    int maxfdp1 = std::max(listenfd, udpfd) + 1;
    char buf[MAXLINE];

    while (1)
    {
        FD_SET(listenfd, &rset);
        FD_SET(udpfd, &rset);

        ret = select(maxfdp1, &rset, NULL, NULL, NULL);
        if (-1 == ret)
        {
            if (EINTR == errno)
            {
                continue;
            }
            else
            {
                perror("select");
                exit(errno);
            }
        }

        //tcp
        if (FD_ISSET(listenfd, &rset))
        {
            int connfd = accept(listenfd, NULL, NULL);
            if (-1 == connfd)
            {
                perror("accept");
                exit(errno);
            }

            ret = fork();
            if (-1 == ret)
            {
                perror("fork");
                exit(errno);
            }
            else if (ret > 0)   //parent
            {
                close(connfd);
            }
            else                //child
            {
                close(listenfd);
                while (1)
                {
                    bzero(&buf, sizeof(buf));
                    int n = read(connfd, buf, sizeof(buf));
                    if (-1 == n)
                    {
                        perror("read");
                        exit(errno);
                    }
                    else if (0 == n)
                    {
                        exit(0);
                    }
                    else
                    {
                        write(connfd, buf, n);
                    }
                }
            }
        }

        //udp
        if (FD_ISSET(udpfd, &rset))
        {
            struct sockaddr_in cliaddr;
            bzero(&cliaddr, sizeof(cliaddr));
            bzero(&buf, sizeof(buf));
            socklen_t len = sizeof(cliaddr);
            int n = recvfrom(udpfd, buf, sizeof(buf), 0, (SA*)&cliaddr, &len);
            if (-1 == n)
            {
                perror("recvfrom");
                exit(errno);
            }

            n = sendto(udpfd, buf, n, 0, (SA*)&cliaddr, len);
            if (-1 == n)
            {
                perror("sendto");
                exit(errno);
            }
        }
    }

    return 0;
}

