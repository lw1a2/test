#include <unistd.h>
#include <strings.h>
#include <cstdio>
#include <errno.h>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>
#include <iostream>
#include <sys/wait.h>

using namespace std;

typedef struct sockaddr SA;

#define MAXLINE     4096

void str_echo(int sockfd)
{
    ssize_t n = 0;
    char buf[MAXLINE];
    bzero(buf, sizeof(buf));

    while (1)
    {
        while ( (n = read(sockfd, buf, MAXLINE)) > 0)
        {
            int ret = write(sockfd, buf, n);
            if (-1 == ret)
            {
                perror("write");
                exit(errno);
            }
        }
        if (n < 0 && EINTR == errno)
        {
            continue;
        }
        else if (n < 0)
        {
            perror("read");
            exit(errno);
        }
        else if (0 == n)    //¿Í»§¶ËÊäÈëEOF
        {
            break;
        }
    }
}

void sig_chld(int signo)
{
    pid_t pid = 0;
    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
    {
        cout << "child " << pid << " terminated" << endl;
    }
}

int main()
{
    struct sigaction sa;
    sa.sa_flags = 0;
#ifdef SA_RESTART
    sa.sa_flags |= SA_RESTART;
#endif
    sa.sa_handler = sig_chld;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGCHLD, &sa, NULL);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listenfd)
    {
        perror("socket listenfd");
        return errno;
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
        return errno;
    }

    ret = bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
    if (-1 == ret)
    {
        perror("bind");
        return errno;
    }

    ret = listen(listenfd, 5);
    if (-1 == ret)
    {
        perror("listen");
        return errno;
    }

    while (1)
    {
        int connfd = accept(listenfd, NULL, NULL);
        if (-1 == connfd)
        {
            if (EINTR == errno)
            {
                continue;
            }
            else
            {
                perror("accept");
                return errno;
            }
        }

        pid_t childpid = fork();
        if (-1 == childpid)
        {
            perror("fork");
            return errno;
        }
        else if (childpid > 0)  //parent
        {
            close(connfd);
        }
        else                    //child
        {
            close(listenfd);
            str_echo(connfd);
            exit(0);
        }
    }

    return 0;
}

