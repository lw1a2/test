#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <sys/un.h>

using namespace std;

int main()
{
    int ret = 0;

    int listen_sock = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (-1 == listen_sock)
    {
        cout << "socket: " << strerror(errno) << endl;
        return errno;
    }

    struct sockaddr_un addr;
    bzero(&addr, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    const char *path = "/tmp/pass_descriptor";
    strncpy(addr.sun_path, path, strlen(path));

    unlink(path);

    ret = bind(listen_sock, (struct sockaddr *)&addr, sizeof(addr));
    if (-1 == ret)
    {
        cout << "bind: " << strerror(errno) << endl;
        return errno;
    }

    ret = listen(listen_sock, 5);
    if (-1 == ret)
    {
        cout << "listen: " << strerror(errno) << endl;
        return errno;
    }

    int conn_sock = accept(listen_sock, NULL, NULL);
    if (-1 == conn_sock)
    {
        cout << "accept: " << strerror(errno) << endl;
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


    struct iovec iov[1];
    iov[0].iov_len = 1;
    char c;
    iov[0].iov_base = &c;
    msg.msg_iovlen = 1;
    msg.msg_iov = iov;

    int n = recvmsg(conn_sock, &msg, 0);
    if (-1 == n)
    {
        cout << "recvmsg: " << strerror(errno) << endl;
        return errno;
    }

    if (msg.msg_controllen > 0)
    {
        int fd = *(int *)CMSG_DATA(CMSG_FIRSTHDR(&msg)); 
        char buf[1024];
        bzero(buf, sizeof(buf));
        n = read(fd, buf, sizeof(buf));
        if (-1 == n)
        {
            cout << "read: " << strerror(errno) << endl;
            return errno;
        }

        cout << buf << endl;
    }
    else 
    {
        cout << "get descriptor failed" << endl;
    }

    return 0;
}
