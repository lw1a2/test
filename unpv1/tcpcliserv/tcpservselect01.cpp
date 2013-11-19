#include <unistd.h>
#include <sys/socket.h>
#include <strings.h>
#include <sys/types.h>
#include <errno.h>
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>
#include <list>

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

    fd_set rset, allset;
    FD_ZERO(&allset);
    int maxfdp1 = listenfd + 1;
    list<int> connfds;

    FD_SET(listenfd, &allset);

    while (1)
    {
        rset = allset;  //使用allset，这样便于重设rset
        int nreads = select(maxfdp1, &rset, NULL, NULL, NULL);
        if (-1 == nreads)
        {
            perror("select");
            exit(errno);
        }

        if (FD_ISSET(listenfd, &rset))
        {
            int connfd = accept(listenfd, NULL, NULL);
            if (-1 == connfd)
            {
                perror("accept");
                exit(errno);
            }
            if (connfd >= maxfdp1)
            {
                maxfdp1 = connfd + 1;
            }
            --nreads;
            FD_SET(connfd, &allset);    //allset的设置和connfds保持同步
            connfds.push_back(connfd);
        }

        list<int>::iterator it = connfds.begin();
        while (it != connfds.end() && nreads > 0)
        {
            if (FD_ISSET(*it, &rset))
            {
                --nreads;
                char buf[MAXLINE];
                bzero(buf, sizeof(buf));

                int n = read(*it, buf, MAXLINE);
                if (-1 == n)
                {
                    perror("read");
                    exit(errno);
                }
                else if (0 == n)
                {
                    close(*it);
                    FD_CLR(*it, &allset);   //allset的清除和connfds保持同步
                    it = connfds.erase(it);
                    continue;
                }
                else
                {
                    write(*it, buf, n);
                }
            }
            ++it;
        }

    }

    return 0;
}

