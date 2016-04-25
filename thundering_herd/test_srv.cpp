#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(6666);
    if (inet_pton(AF_INET, "172.22.15.230", &serv.sin_addr) != 1) {
        printf("inet_pton server 172.22.15.230 failed\n");
        return 1;
    }

    int ret = 0;
    int sock = -1;
    int on = 1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock) {
        perror("socket");
        return errno;
    }
    ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (-1 == ret) {
        perror("setsockopt");
        return errno;
    }
    // bind will be failed when it invokes in the second process
    ret = bind(sock, (struct sockaddr*)&serv, sizeof(serv));
    if (-1 == ret)
    {
        perror("bind server");
        return errno;
    }
    ret = listen(sock, 5);
    if (-1 == ret) {
        perror("listen");
        return errno;
    }

    while (1) {
        int new_sock = accept(sock, NULL, NULL);
        if (new_sock < 0) {
            perror("accept");
        }
    }

    return 0;
}

