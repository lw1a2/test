#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <strings.h>
#include <iostream>
#include <string.h>
#include <errno.h>

using namespace std;

int main()
{
    const char* path = "./path";
    int ret = 0;

    int sock = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (-1 == sock)
    {
        cout << "socket: " << strerror(errno) << endl;
        return errno;
    }

    struct sockaddr_un addr;
    bzero(&addr, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    strncpy(addr.sun_path, path, strlen(path));
    cout << "addr len: " << SUN_LEN(&addr) << endl;

    unlink(path);

    ret = bind(sock, (struct sockaddr*)&addr, SUN_LEN(&addr));
    if (-1 == ret)
    {
        cout << "bind: " << strerror(errno) << endl;
        return errno;
    }

    struct sockaddr_un addr2;
    bzero(&addr2, sizeof(addr2));
    socklen_t len = sizeof(addr2);
    ret = getsockname(sock, (struct sockaddr*)&addr2, &len);
    if (-1 == ret)
    {
        cout << "getsockname: " << strerror(errno) << endl;
        return errno;
    }

    cout << "sock name: " << addr2.sun_path << endl;

    ret = listen(sock, 5);
    if (-1 == ret)
    {
        cout << "listen: " << strerror(errno) << endl;
        return errno;
    }

    int new_sock = accept(sock, NULL, NULL);
    if (-1 == new_sock)
    {
        cout << "accept: " << strerror(errno) << endl;
        return errno;
    }

    pause();

    return 0;
}
