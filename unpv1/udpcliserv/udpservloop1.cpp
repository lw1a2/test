#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <errno.h>
#include <cstdio>
#include <iostream>
#include <signal.h>
#include <cstdlib>

using namespace std;

typedef struct sockaddr SA;

#define MAXLINE     4096

static int count;

void recvfrom_int(int signo)
{
    cout << "\nreceived " << count << " datagrams" << endl;
    exit(0);
}

void dg_echo(int sockfd, SA* pcliaddr, socklen_t clilen)
{
    int n = 0;
    socklen_t len = 0;
    char mesg[MAXLINE];
    bzero(mesg, sizeof(mesg));

    struct sigaction sa;
    sa.sa_handler = recvfrom_int;
    sigaction(SIGINT, &sa, NULL);

    for (;;)
    {
        len = clilen;
        n = recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
        if (-1 == n)
        {
            perror("recvfrom");
            return;
        }
        ++count;
    }
}

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sockfd)
    {
        perror("socket");
        return errno;
    }

    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8888);

    int ret = bind(sockfd, (SA*)&servaddr, sizeof(servaddr));
    if (-1 == ret)
    {
        perror("bind");
        return errno;
    }
    
    int recvbuf = 0;
    socklen_t recvbuf_len = sizeof(int);
    ret = getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recvbuf, &recvbuf_len);
    if (-1 == ret)
    {
        perror("getsockopt");
        return errno;
    }
    else
    {
        cout << "SO_RCVBUF default: " << recvbuf << endl;
    }
    //改变缓冲区大小似乎没用
    recvbuf = 500000;
    ret = setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recvbuf, sizeof(recvbuf));
    if (-1 == ret)
    {
        perror("setsockopt");
        return errno;
    }
    else
    {
        cout << "SO_RCVBUF: " << recvbuf << endl;
    }


    dg_echo(sockfd, (SA*)&cliaddr, sizeof(cliaddr));

    return 0;
}


