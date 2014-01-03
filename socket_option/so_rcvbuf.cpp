#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>

int main()
{
    int ret = 0;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock)
    {
        perror("socket");
        return errno;
    }

    int opt = 1;
    socklen_t len = sizeof(opt);
    // net.ipv4.tcp_rmem is for global setting
    ret = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &opt, &len);
    if (-1 == ret)
    {
        perror("getsockopt");
        return errno;
    }

    printf("SO_RCVBUF: %d\n", opt);

    return 0;
}

