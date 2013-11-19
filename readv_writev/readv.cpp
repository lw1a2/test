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

    const int BUFMAX = 1024;

    struct iovec iov[2];
    bzero(iov, sizeof(iov));
    iov[0].iov_len = BUFMAX;
    iov[0].iov_base = new char[BUFMAX];
    bzero(iov[0].iov_base, BUFMAX);
    
    iov[1].iov_len = BUFMAX;
    iov[1].iov_base = new char[BUFMAX];
    bzero(iov[1].iov_base, BUFMAX);

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

    ret = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    if (-1 == ret)
    {
        cout << "bind" << strerror(errno) << endl;
        return errno;
    }

    int n = readv(sock, iov, 2);
    if (-1 == n)
    {
        cout << "readv" << strerror(errno) << endl;
        return errno;
    }

    cout << (char*)iov[0].iov_base << endl;
    cout << (char*)iov[1].iov_base << endl;

    return 0;
}

