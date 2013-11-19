//ipv6作为服务器端（双栈主机），ipv4作为客户端的例子
//此程序为服务器端。客户端可以通过如下命令来模拟：
//telnet x.x.x.x 8888
//可以看到程序打印出了ipv4映射的ipv6地址
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>

using namespace std;

int main()
{
    int ret = 0;
    struct sockaddr_in6 serv;
    bzero(&serv, sizeof(serv));
    serv.sin6_family = AF_INET6;
    serv.sin6_port = htons(8888);
    serv.sin6_addr = in6addr_any;
//  ret = inet_pton(AF_INET6, "fe80::92e2:baff:fe18:2a54", &serv.sin6_addr);
//  if (-1 == ret)
//  {
//      cout << "inet_pton: " << strerror(errno) << endl;
//      return errno;
//  }
//  else if (0 == ret)
//  {
//      cout << "src does not contain a character string representing a valid network address in the specified address family" << endl;
//      return -1;
//  }

    int sock = socket(AF_INET6, SOCK_STREAM, 0);
    if (-1 == sock)
    {
        cout << "socket: " << strerror(errno) << endl;
        return errno;
    }

    int opt = 1;
    ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (-1 == ret)
    {
        cout << "setsockopt: " << strerror(errno) << endl;
        return errno;
    }

    ret = bind(sock, (struct sockaddr*)&serv, sizeof(serv));
    if (-1 == ret)
    {
        cout << "bind: " << strerror(errno) << endl;
        return errno;
    }

    ret = listen(sock, 5);
    if (-1 == ret)
    {
        cout << "listen: " << strerror(errno) << endl;
        return errno;
    }

    struct sockaddr_in6 cli;
    bzero(&cli, sizeof(cli));
    socklen_t len = sizeof(cli);
    int sock_cli = accept(sock, (struct sockaddr*)&cli, &len);
    if (-1 == sock_cli)
    {
        cout << "accept: " << strerror(errno) << endl;
        return errno;
    }

    char buf[INET6_ADDRSTRLEN];
    bzero(buf, sizeof(buf));
    if (!inet_ntop(AF_INET6, &cli.sin6_addr, buf, sizeof(buf)))
    {
        cout << "inet_ntop: " << strerror(errno) << endl;
        return errno;
    }
    cout << "client ip: " << buf << endl;
    cout << "client port: " << ntohs(cli.sin6_port) << endl;

    return 0;
}

