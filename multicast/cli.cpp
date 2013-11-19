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
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sock)
    {
        perror("socket");
        return errno;
    }

    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    if (inet_pton(AF_INET, "224.0.0.88", &serv.sin_addr) != 1)
    {
        cout << "inet_pton failed" << endl;
        return 1;
    }
    serv.sin_port = htons(8888);

    char buf[10240];

    for (int i = 0; i < 1000; ++i)
    {
        bzero(buf, sizeof(buf));
        snprintf(buf, sizeof(buf), "%d", i);
        //strncpy(buf, "test", strlen("test"));

        int n = sendto(sock, buf, strlen(buf), 0, (sockaddr*)&serv, sizeof(serv));
        if (-1 == n)
        {
            perror("sendto");
            return errno;
        }
        else
        {
            cout << "sent " << buf << endl;
        }
        sleep(3);
    }

    return 0;
}

