#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <iostream>
#include <sys/select.h>

using namespace std;

int main()
{
    int ret = 0;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock)
    {
        perror("socket");
        return errno;
    }

    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    inet_pton(AF_INET, "172.173.1.1", &serv.sin_addr);
    serv.sin_port = htons(8888);

    ret = connect(sock, (struct sockaddr *)&serv, sizeof(serv));
    if (-1 == ret)
    {
        perror("connect");
        return errno;
    }

    int n = -1;

    n = send(sock, "123", 3, 0);
    if (-1 == n)
    {
        perror("send"); 
        return errno;
    }
    else
    {
        cout << "send " << n << " bytes" << endl;
    }

    n = send(sock, "4", 1, MSG_OOB);
    if (-1 == n)
    {
        perror("send");
        return errno;
    }
    else
    {
        cout << "send " << n << " bytes" << endl;
    }

    n = send(sock, "5", 1, 0);
    if (-1 == n)
    {
        perror("send");
        return errno;
    }
    else
    {
        cout << "send " << n << " bytes" << endl;
    }

    return 0;
}

