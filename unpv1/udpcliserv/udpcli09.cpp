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

    ret = connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
    if (-1 == ret)
    {
        perror("connect");
        return errno;
    }

    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    ret = getsockname(sockfd, (SA*)&cliaddr, &len);
    if (-1 == ret)
    {
        perror("getsockname");
        return errno;
    }

    char addrbuf[INET_ADDRSTRLEN];
    bzero(addrbuf, sizeof(addrbuf));
    cout << "client address: " << inet_ntop(AF_INET, &cliaddr.sin_addr, addrbuf, sizeof(addrbuf))
        << endl;
    return 0;
}



