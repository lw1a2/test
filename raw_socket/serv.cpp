#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    int ret = 0;
    int sock_listen = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock_listen) {
        perror("socket");
        return errno;
    }

    int opt = 1;
    ret = setsockopt(sock_listen, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));
    if (-1 == ret) {
        perror("setsockopt");
        return errno;
    }

    opt = 1;
    ret = setsockopt(sock_listen, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (-1 == ret) {
        perror("setsockopt");
        return errno;
    }

    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    inet_pton(AF_INET, "10.16.1.2", &serv.sin_addr);
    serv.sin_port = htons(8888);

    ret = bind(sock_listen, (struct sockaddr *)&serv, sizeof(serv));
    if (-1 == ret) {
        perror("bind");
        return errno;
    }

    ret = listen(sock_listen, 5);
    if (-1 == ret) {
        perror("listen");
        return errno;
    }

    while (1) {
        sockaddr_in cli;
        socklen_t cli_len = sizeof(cli);
        int sock_conn = accept(sock_listen, (sockaddr *)&cli, &cli_len);
        if (-1 == sock_conn) {
            perror("accept");
            return errno;
        }

        close(sock_conn);
    }

    return 0;
}

