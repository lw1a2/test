#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <errno.h>
#include <cstdio>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

typedef struct sockaddr SA;

#define MAXLINE     4096

void dg_cli(FILE *fp, int sockfd, SA* pservaddr, socklen_t servlen)
{
    int n = 0;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    bzero(sendline, sizeof(sendline));
    bzero(recvline, sizeof(recvline));

    int ret = connect(sockfd, (SA*)pservaddr, servlen);
    if (-1 == ret)
    {
        perror("connect");
        return;
    }

    while (fgets(sendline, MAXLINE, fp) != NULL)
    {
        n = write(sockfd, sendline, strlen(sendline));
        if (-1 == n)
        {
            perror("write");
            return;
        }

        n = read(sockfd, recvline, MAXLINE);
        if (-1 == n)
        {
            perror("read");
            return;
        }
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF)
        {
            perror("fputs");
            return;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "usage: " << argv[0] << " <IPaddress>" << endl;
        return 0;
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sockfd)
    {
        perror("socket");
        return errno;
    }

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8888);
    int ret = inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    if (-1 == ret)
    {
        perror("inet_pton");
        return errno;
    }

    dg_cli(stdin, sockfd, (SA*)&servaddr, sizeof(servaddr));

    return 0;
}



