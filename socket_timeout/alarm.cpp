#include <iostream>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <signal.h>

using namespace std;

void sig_alarm(int)
{
    write(1, "sig_alarm\n", strlen("sig_alarm"));
}

int main()
{
    int ret = 0;

    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sa.sa_handler = sig_alarm;
    ret = sigaction(SIGALRM, &sa, NULL);
    if (-1 == ret)
    {
        cout << "sigaction: " << strerror(errno) << endl;
        return errno;
    }

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    if (inet_pton(AF_INET, "127.0.0.1", (struct sockaddr*)&addr.sin_addr) != 1)
    {
        cout << "inet_pton failed" << endl;
        return 1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock)
    {
        cout << "socket: " << strerror(errno) << endl;
        return errno;
    }

    ret = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    if (-1 == ret)
    {
        cout << "connect: " << strerror(errno) << endl;
        return errno;
    }

    alarm(1);

    char buf[1024];
    bzero(buf, sizeof(buf));
    int n = read(sock, buf, sizeof(buf));
    if (-1 == n)
    {
        cout << "read: " << strerror(errno) << endl;
        return errno;
    }

    return 0;
}
