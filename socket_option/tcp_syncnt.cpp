#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

int main()
{
    int ret = 0;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock)
    {
        perror("socket");
        return errno;
    }

    int tcp_syn_retries = 0;
    socklen_t len = sizeof(tcp_syn_retries);
    ret = setsockopt(sock, IPPROTO_TCP, TCP_SYNCNT, &tcp_syn_retries, len);
        if (-1 == ret)
    {
        perror("setsockopt");
        return errno;
    }

    ret = getsockopt(sock, IPPROTO_TCP, TCP_SYNCNT, &tcp_syn_retries, &len);
    if (-1 == ret)
    {
        perror("getsockopt");
        return errno;
    }

    printf("TCP_SYNCNT: %d\n", tcp_syn_retries);

    return 0;
}

