#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <sys/un.h>
#include <fcntl.h>

using namespace std;

int main()
{
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
    const char *path = "/tmp/pass_descriptor";
    strncpy(addr.sun_path, path, strlen(path));

//  cout << "sizeof(addr): " << sizeof(addr) << endl;
//  cout << "SUN_LEN(&addr): " << SUN_LEN(&addr) << endl;

    ret = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (-1 == ret)
    {
        cout << "connect: " << strerror(errno) << endl;
        return errno;
    }

    struct msghdr msg;
    bzero(&msg, sizeof(msg));
    union {
        struct cmsghdr cm;
        char control[CMSG_SPACE(sizeof(int))];
    } control_un;
    bzero(&control_un, sizeof(control_un));
    msg.msg_control = control_un.control;
    msg.msg_controllen = sizeof(control_un);
    control_un.cm.cmsg_level = SOL_SOCKET;
    control_un.cm.cmsg_type = SCM_RIGHTS;
    control_un.cm.cmsg_len = CMSG_LEN(sizeof(int));
    int fd = open("./Makefile", O_RDONLY);
    if (-1 == fd)
    {
        cout << "open ./Makefile: " << strerror(errno) << endl;
        return errno;
    }
    *((int *)CMSG_DATA(&control_un.cm)) = fd;
    struct iovec iov[1];
    char c;
    iov[0].iov_base = &c;
    iov[0].iov_len = 1;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;

    int n = sendmsg(sock, &msg, 0);
    if (-1 == n)
    {
        cout << "sendmsg: " << strerror(errno) << endl;
        return errno;
    }

    return 0;
}
