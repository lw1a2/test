//ipv6��Ϊ�ͻ��ˣ�˫ջ��������ipv4��Ϊ�������˵�����
//�˳���Ϊ�ͻ��ˡ��������˿���ͨ������IP��ַ��v4�ķ�������22�˿���ģ�⣺
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
    serv.sin6_port = htons(22);
//  serv.sin6_addr = in6addr_any;
    ret = inet_pton(AF_INET6, "::ffff:172.173.3.1", &serv.sin6_addr);
    if (-1 == ret)
    {
        cout << "inet_pton: " << strerror(errno) << endl;
        return errno;
    }
    else if (0 == ret)
    {
        cout << "src does not contain a character string representing a valid network address in the specified address family" << endl;
        return -1;
    }

    int sock = socket(AF_INET6, SOCK_STREAM, 0);
    if (-1 == sock)
    {
        cout << "socket: " << strerror(errno) << endl;
        return errno;
    }

    ret = connect(sock, (struct sockaddr*)&serv, sizeof(serv));
    if (-1 == ret)
    {
        cout << "connect: " << strerror(errno) << endl;
        return errno;
    }

    struct sockaddr_in6 cli;
    bzero(&cli, sizeof(cli));
    socklen_t len = 0;
    ret = getsockname(sock, (struct sockaddr*)&cli, &len);
    if (-1 == ret)
    {
        cout << "getsockname: " << strerror(errno) << endl;
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

