#include <netinet/in.h>
#include <cstdio>
#include <strings.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <errno.h>
#include <arpa/inet.h>

typedef struct sockaddr SA;

#define MAXLINE     4096

using namespace std;

void str_cli(FILE *fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];
    bzero(sendline, sizeof(sendline));
    bzero(recvline, sizeof(recvline));

    while (fgets(sendline, MAXLINE, fp) != NULL)
    {
        write(sockfd, sendline, strlen(sendline));
        
        int n = read(sockfd, recvline, MAXLINE);
        if (-1 == n)
        {
            perror("read");
            exit(errno);
        }
        else if (0 == n)
        {
            cout << "str_cli: server terminated prematurely" << endl;
            exit(0);
        }

        fputs(recvline, stdout);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "usage: " << argv[0] << " <IPaddress>" << endl;
        exit(0);
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8888);
    int ret = inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    if (0 == ret)
    {
        cout << "IP address is invalid" << endl;
        exit(0);
    }
    else if (-1 == ret)
    {
        cout << "Address family is invalid" << endl;
        exit(errno);
    }

    ret = connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
    if (-1 == ret)
    {
        perror("connect");
        exit(errno);
    }

    str_cli(stdin, sockfd);

    return 0;
}

