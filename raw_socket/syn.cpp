#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


int main()
{
    int sock_out = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

    if (-1 == sock_out) {
        perror("socket output");
        return errno;
    }

    return 0;
}
