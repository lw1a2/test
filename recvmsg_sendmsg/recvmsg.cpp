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

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock)
    {
        cout << "socket: " << strerror(errno) << endl;
        return errno;
    }

    int on = 1;
    ret = setsockopt(sock, IPPROTO_IP, IP_PKTINFO, &on, sizeof(on));
    if (-1 == ret)
    {
        cout << "setsockopt: " << strerror(errno) << endl;
        return errno;
    }

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(55555);
    if (inet_pton(AF_INET, "172.173.1.107", &addr.sin_addr) != 1)
    {
        cout << "inet_pton failed" << endl;
        return 1;
    }

    ret = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (-1 == ret)
    {
        cout << "bind: " << strerror(errno) << endl;
        return errno;
    }

    int flags = 0;
    struct msghdr msg;
    bzero(&msg, sizeof(msg));
    msg.msg_name = new char[1024];
    msg.msg_namelen = 1024;
    msg.msg_control = new char[1024];
    msg.msg_controllen = 1024;

    int n = recvmsg(sock, &msg, 0);
    if (-1 == n)
    {
        cout << "recvmsg: " << strerror(errno) << endl;
        return errno;
    }

    struct sockaddr_in peer;
    bzero(&peer, sizeof(peer));

    memcpy(&peer, msg.msg_name, msg.msg_namelen);
    char buf[INET_ADDRSTRLEN];
    bzero(buf, sizeof(buf));
    cout << "peer: " << inet_ntop(AF_INET, (struct sockaddr_in *)&peer.sin_addr, buf, sizeof(buf))
        << ": " << ntohs(peer.sin_port) << endl;
    bzero(buf, sizeof(buf));
    if (msg.msg_controllen > 0) 
    {
        struct sockaddr_in local;
        struct in_pktinfo *in = (struct in_pktinfo *)CMSG_DATA((struct cmsghdr *)msg.msg_control);  
        memcpy(&local.sin_addr, &(in->ipi_addr), sizeof(struct in_addr));
        cout << "local: " << inet_ntop(AF_INET, (struct sockaddr_in *)&local.sin_addr, buf, sizeof(buf)) << endl;
    }

//  cout << (char*)iov[0].iov_base << endl;
//  cout << (char*)iov[1].iov_base << endl;



    return 0;
}

