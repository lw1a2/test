#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <sys/wait.h>
#include <signal.h>
#include <fstream>
#include <string>

using namespace std;

void sig_chld(int)
{
    pid_t pid;

    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
    {
//      printf("child %d exit\n", pid);
    }
}


int main()
{
    int ret = 0;
    int sock_listen = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock_listen)
    {
        perror("socket");
        return errno;
    }

    int opt = 1;
    ret = setsockopt(sock_listen, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));
    if (-1 == ret)
    {
        perror("setsockopt");
        return errno;
    }

    opt = 1;
    ret = setsockopt(sock_listen, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (-1 == ret)
    {
        perror("setsockopt");
        return errno;
    }

    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    inet_pton(AF_INET, "10.16.1.2", &serv.sin_addr);
    //serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(8888);

    ret = bind(sock_listen, (struct sockaddr*)&serv, sizeof(serv));
    if (-1 == ret)
    {
        perror("bind");
        return errno;
    }

    ret = listen(sock_listen, 5);
    if (-1 == ret)
    {
        perror("listen");
        return errno;
    }

    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sa.sa_handler = sig_chld;
    ret = sigaction(SIGCHLD, &sa, NULL);
    if (-1 == ret)
    {
        perror("sigaction");
        return errno;
    }

    while (1)
    {
        sockaddr_in cli;
        socklen_t cli_len = sizeof(cli);
        int sock_conn = accept(sock_listen, (sockaddr*)&cli, &cli_len);
        if (-1 == sock_conn)
        {
            if (EINTR == errno)
            {
                continue;
            }
            else
            {
                perror("accept");
                return errno;
            }
        }

        pid_t pid = fork();
        if (0 == pid)       //child
        {
            close(sock_listen);
            char buf[102400];
            int i = 0;
            while (1)
            {
                bzero(buf, sizeof(buf));
                int n = read(sock_conn, buf, sizeof(buf));
                if (-1 == n)
                {
                    perror("read");
                    return errno;
                }
                else if (0 == n)
                {
                    return 0;
                }

                char addr_buf[INET_ADDRSTRLEN];
                bzero(addr_buf, sizeof(addr_buf));
                if (inet_ntop(AF_INET, &cli.sin_addr, addr_buf, sizeof(addr_buf)))
                {
//                  printf("%s.%d: ", addr_buf, ntohs(cli.sin_port));
                }
//              printf("%s", buf);

                //echo
                bzero(buf, sizeof(buf));
                const char * resp = "HTTP/1.1 200 OK\r\nDate: Mon, 15 Jul 2013 04:34:06 GMT\r\nServer: Apache/2.2.15 (CentOS)\r\nLast-Modified: Mon, 27 May 2013 05:48:31 GMT\r\nETag: \"2233e1-c800-4ddacb2d83700\"\r\nAccept-Ranges: bytes\r\nContent-Length: 51200\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n";
                int len = strlen(resp);
                strncpy(buf, resp, len);
                ifstream fin("./index.html");

                char c;
                int size = 0;
                while (fin.get(c))
                {
                    strncpy(buf + len + size, &c, 1);
                    size++;
                }
                n = write(sock_conn, buf, strlen(buf));
                if (-1 == n)
                {
                    perror("write");
                    return errno;
                }
//              printf("%s", buf);
                bzero(buf, sizeof(buf));
            }
        }
        else if (pid > 0)   //parent
        {
            close(sock_conn);
        }
        else
        {
            perror("fork");
            return errno;
        }
    }

    return 0;
}

