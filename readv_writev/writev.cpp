#include <iostream>
#include <strings.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#inlcude <sys/uio.h>

using namespace std;

int main()
{
    int ret = 0;

    struct iovec iov[2];
    bzero(iov, sizeof(iov));
    iov[0].iov_len = strlen("hello");
    iov[0].iov_base = new char[iov[0].iov_len];
    memcpy(iov[0].iov_base, "hello", iov[0].iov_len);
    
    iov[1].iov_len = strlen("world");
    iov[1].iov_base = new char[iov[1].iov_len];
    memcpy(iov[1].iov_base, "world", iov[1].iov_len);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sock)
    {
        cout << "socket" << strerror(errno) << endl;
        return errno;
    }

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(58888);
    if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) != 1)
    {
        cout << "inet_pton failed" << endl;
        return 1;
    }

    ret = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    if (-1 == ret)
    {
        cout << "connect" << strerror(errno) << endl;
        return errno;
    }

    int n = writev(sock, iov, 2);
    if (-1 == n)
    {
        cout << "writev" << strerror(errno) << endl;
        return errno;
    }

    return 0;
}
