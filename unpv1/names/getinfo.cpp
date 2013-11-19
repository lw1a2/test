#include <netdb.h>
#include <iostream>
#include <cstdlib>
#include <strings.h>
#include <cstdio>
#include <arpa/inet.h>
#include <errno.h>

using namespace std;

int main()
{
    struct addrinfo hints, *res = NULL, *ressave = NULL;
    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    int ret = getaddrinfo("RHEL", "ftp", &hints, &res);
    if (ret != 0)
    {
        cout << gai_strerror(ret) << endl;
        exit(ret);
    }

    ressave = res;
    while (res)
    {
        if (AF_INET == res->ai_family)
        {
            char buf[INET_ADDRSTRLEN];
            bzero(buf, sizeof(buf));
            if (NULL == inet_ntop(res->ai_family, &((struct sockaddr_in*)res->ai_addr)->sin_addr, buf, sizeof(buf)))
            {
                perror("inet_ntop");
                freeaddrinfo(ressave);
                exit(errno);
            }
            cout << buf;
        }
        else if (AF_INET6 == res->ai_family)
        {
            char buf[INET6_ADDRSTRLEN];
            bzero(buf, sizeof(buf));
            if (NULL == inet_ntop(res->ai_family, &((struct sockaddr_in6*)res->ai_addr)->sin6_addr, buf, sizeof(buf)))
            {
                perror("inet_ntop");
                freeaddrinfo(ressave);
                exit(errno);
            }
            cout << buf;
        }
        char host[NI_MAXHOST];
        bzero(host, sizeof(host));
        char serv[NI_MAXSERV];
        bzero(serv, sizeof(serv));
        ret = getnameinfo(res->ai_addr, sizeof(*res->ai_addr), host, sizeof(host),
                          serv, sizeof(serv), 0);
        if (ret != 0)
        {
            cout << endl << gai_strerror(ret) << endl;
            exit(ret);
        }
        cout << " " << host << " " << serv << endl;
        res = res->ai_next;
    }

    freeaddrinfo(ressave);

    

    return 0;
}
