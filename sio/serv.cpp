#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int sock = -1;

void sig_io(int)
{
    char buf[1024];
    bzero(buf, sizeof(buf));
    int n = recvfrom(sock, buf, sizeof(buf), 0, NULL, NULL);
    if (-1 == n)
    {
        write(1, "recvfrom", strlen("recvfrom"));
        write(1, strerror(errno), strlen(strerror(errno)));
        return;
    }

    write(1, buf, strlen(buf)); 
    write(1, "\n", strlen("\n")); 
}

int main()
{
    int ret = 0;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sock)
    {
        perror("socket");
        return errno;
    }

    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sa.sa_handler = sig_io;
    ret = sigaction(SIGIO, &sa, NULL);
    if (-1 == ret)
    {
        perror("sigaction"); 
        return errno; 
    }

    ret = fcntl(sock, F_SETOWN, getpid());
    if (-1 == ret)
    {
        perror("fcntl F_SETOWN"); 
        return errno;
    }

    int flag = fcntl(sock, F_GETOWN, 0);
    if (-1 == flag) 
    {
        perror("fcntl F_GETOWN"); 
        return errno;
    }

    flag |= O_ASYNC; 
    ret = fcntl(sock, F_SETFL, flag);
    if (-1 == ret)
    {
        perror("fcntl F_SETFL"); 
        return errno;
    }

    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(58888);
    inet_pton(AF_INET, "172.173.1.1", &serv.sin_addr);

    ret = bind(sock, (sockaddr*)&serv, sizeof(serv));
    if (-1 == ret)
    {
        perror("bind");
        return errno;
    }

    while (1)
    {
        pause();
    }

    return 0;
}

