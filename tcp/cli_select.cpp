#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <iostream>
#include <sys/select.h>

using namespace std;

int main()
{
    int ret = 0;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock)
    {
        perror("socket");
        return errno;
    }

    int opt = 1;
    ret = setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));
    if (-1 == ret)
    {
        perror("setsockopt");
        return errno;
    }

    struct sockaddr_in cli;
    bzero(&cli, sizeof(cli));
    cli.sin_family = AF_INET;
    inet_pton(AF_INET, "10.1.1.1", &cli.sin_addr);
    ret = bind(sock, (struct sockaddr*)&cli, sizeof(cli));
    if (-1 == ret)
    {
        perror("bind");
        return errno;
    }

//  struct sockaddr_in tmp;
//  bzero(&tmp, sizeof(tmp));
//  socklen_t len = sizeof(tmp);
//  ret = getsockname(sock, (sockaddr*)&tmp, &len);
//  if (-1 == ret)
//  {
//      perror("getsockname");
//      return errno;
//  }

//  char addrbuf[INET_ADDRSTRLEN];
//  bzero(addrbuf, sizeof(addrbuf));
//  if (!inet_ntop(AF_INET, &tmp.sin_addr, addrbuf, INET_ADDRSTRLEN))
//  {
//      perror("inet_ntop");
//      return errno;
//  }
//  else
//  {
//      cout << addrbuf;
//  }
//  cout << ": " << ntohs(tmp.sin_port) << endl;

    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    inet_pton(AF_INET, "10.1.1.1", &serv.sin_addr);
    serv.sin_port = htons(8888);

    ret = connect(sock, (struct sockaddr*)&serv, sizeof(serv));
    if (-1 == ret)
    {
        perror("connect");
        return errno;
    }

//  bzero(&tmp, sizeof(tmp));
//  len = sizeof(tmp);
//  ret = getpeername(sock, (sockaddr*)&tmp, &len);
//  if (-1 == ret)
//  {
//      perror("getpeername");
//      return errno;
//  }
//  bzero(addrbuf, sizeof(addrbuf));
//  if (!inet_ntop(AF_INET, &tmp.sin_addr, addrbuf, INET_ADDRSTRLEN))
//  {
//      perror("inet_ntop");
//      return errno;
//  }
//  else
//  {
//      cout << addrbuf;
//  }
//  cout << ": " << ntohs(tmp.sin_port) << endl;

    char buf[10240];
    bool input_over = false;

    while (1)
    {
        int n = 0;
        fd_set rset;
        FD_ZERO(&rset);
        if (!input_over)
        {
            FD_SET(STDIN_FILENO, &rset);
        }
        FD_SET(sock, &rset);
        int nfds = select(max(STDIN_FILENO, sock) + 1, &rset, NULL, NULL, NULL);
        if (-1 == nfds)
        {
            perror("select");
            return errno;
        }

        if (FD_ISSET(STDIN_FILENO, &rset))
        {
            bzero(buf, sizeof(buf));
            n = read(STDIN_FILENO, buf, sizeof(buf));
            if (-1 == n)
            {
                perror("read from STDIN_FILENO");
                return errno;
            }
            else if (0 == n)
            {
                shutdown(sock, SHUT_WR);
                input_over = true;
            }

            n = write(sock, buf, n);
            if (-1 == n)
            {
                perror("write");
                return errno;
            }
        }

        if (FD_ISSET(sock, &rset))
        {
            bzero(buf, sizeof(buf));
            n = read(sock, buf, sizeof(buf));
            if (-1 == n)
            {
                perror("read from serv");
                return errno;
            }
            else if (0 == n)
            {
                break;
            }

            printf("echo: %s", buf);
        }
    }

    return 0;
}

