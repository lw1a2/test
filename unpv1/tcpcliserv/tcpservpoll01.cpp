#include <unistd.h>
#include <sys/socket.h>
#include <strings.h>
#include <sys/types.h>
#include <errno.h>
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>
#include <list>
#include <poll.h>

using namespace std;

typedef struct sockaddr SA;

#define MAXLINE 4096

int main()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listenfd)
    {
        perror("socket");
        exit(errno);
    }

    struct sockaddr_in servaddr;
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
        perror("bind");
        exit(errno);
    }

    ret = listen(listenfd, 5);
    if (-1 == ret)
    {
        perror("listen");
        exit(errno);
    }

    const int FDMAX = 1024;
    struct pollfd fds[FDMAX];
    nfds_t nfds = 1;
    list<int> connfds;
    fds[0].fd = listenfd;
    fds[0].events = POLLRDNORM;
    for (int i = 1; i < FDMAX; ++i)
    {
        fds[i].fd = -1;
        fds[i].events = POLLRDNORM;
    }

    while (1)
    {
        int nreads = poll(fds, nfds, -1);
        if (-1 == nreads)
        {
            perror("poll");
            exit(errno);
        }

        if (fds[0].revents & POLLRDNORM)
        {
            int connfd = accept(listenfd, NULL, NULL);
            if (-1 == connfd)
            {
                perror("accept");
                exit(errno);
            }
            ++nfds;
            int i = 1;
            while (i < FDMAX)
            {
                if (-1 == fds[i].fd)
                {
                    fds[i].fd = connfd;
                    break;
                }
                ++i;
            }
            --nreads;
            connfds.push_back(i);
        }

        list<int>::iterator it = connfds.begin();
        while (it != connfds.end() && nreads > 0)
        {
            if (fds[*it].revents & (POLLRDNORM | POLLERR))
            {
                --nreads;
                char buf[MAXLINE];
                bzero(buf, sizeof(buf));

                int n = read(fds[*it].fd, buf, MAXLINE);
                if (-1 == n)
                {
                    perror("read");
                    exit(errno);
                }
                else if (0 == n)
                {
                    close(fds[*it].fd);
                    fds[*it].fd = -1;
                    it = connfds.erase(it);
                    continue;
                }
                else
                {
                    write(fds[*it].fd, buf, n);
                }
            }
            ++it;
        }
    }

    return 0;
}


