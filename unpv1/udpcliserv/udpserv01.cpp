#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <errno.h>
#include <cstdio>

using namespace std;

typedef struct sockaddr SA;

#define MAXLINE     4096

void dg_echo(int sockfd, SA* pcliaddr, socklen_t clilen)
{
    int n = 0;
    socklen_t len = 0;
    char mesg[MAXLINE];
    bzero(mesg, sizeof(mesg));

    for (;;)
    {
        len = clilen;
        n = recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
        if (-1 == n)
        {
            perror("recvfrom");
            return;
        }
        n = sendto(sockfd, mesg, n, 0, pcliaddr, len);
        if (-1 == n)
        {
            perror("sendto");
            return;
        }
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
    
    dg_echo(sockfd, (SA*)&cliaddr, sizeof(cliaddr));

    return 0;
}

