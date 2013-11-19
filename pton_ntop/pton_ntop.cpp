#include <netinet/in.h>
#include <sys/types.h>
#include <strings.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

int main()
{
    sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8888);
    int ret = 0;

    ret = inet_pton(AF_INET, "1.1.1.1", &serv.sin_addr);
    if (ret != 1)
    {
        perror("inet_pton");
        return errno;
    }

    char buf[INET_ADDRSTRLEN];
    if (!inet_ntop(AF_INET, &serv.sin_addr, buf, sizeof(buf)))
    {
        perror("inet_ntop");
        return errno;
    }
    cout << buf << endl;

    return 0;
}

