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
    serv.sin_port = htons(8888);

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
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    ret = bind(sock,(sockaddr*)&serv, sizeof(serv));
    if (-1 == ret) {
        perror("bind INADDR_ANY 8888");
        return errno;
    }
    ret = listen(sock, 5);
    if (-1 == ret) {
        perror("listen INADDR_ANY 8888");
        return errno;
    }



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
    if (inet_pton(AF_INET, "10.1.1.1", &serv.sin_addr) != 1) {
        printf("inet_pton 10.1.1.1 failed\n");
        return 1;
    }
    ret = bind(sock, (sockaddr*)&serv, sizeof(serv));
    if (-1 == ret) {
        perror("bind 10.1.1.1 8888");
        return errno;
    }
    ret = listen(sock, 5);
    if (-1 == ret) {
        perror("listen 10.1.1.1 8888");
        return errno;
    }



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
    if (inet_pton(AF_INET, "10.16.1.2", &serv.sin_addr) != 1) {
        printf("inet_pton 10.16.1.2 failed\n");
        return 1;
    }
    ret = bind(sock, (sockaddr*)&serv, sizeof(serv));
    if (-1 == ret) {
        perror("bind 10.16.1.2 8888");
        return errno;
    }
    ret = listen(sock, 5);
    if (-1 == ret) {
        perror("listen 10.16.1.2 8888");
        return errno;
    }


    return 0;
}

