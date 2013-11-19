#include <netdb.h>
#include <strings.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

int main()
{
    int ret = 0;
    struct addrinfo hint, *res;
    bzero(&hint, sizeof(hint));
    hint.ai_family = AF_INET;
    ret = getaddrinfo("www.sina.com", "http", &hint, &res);
    if (ret != 0)
    {
        cout << "getaddrinfo failed: " << gai_strerror(ret) << endl;
        return ret;
    }

    for (struct addrinfo * p = res; p != NULL; p = p->ai_next)
    {
        char buf[res->ai_addrlen];
        bzero(buf, sizeof(buf));
        cout << "ai_flags: " << p->ai_flags << endl;

        cout << "ai_family: ";
        if (AF_INET == p->ai_family)
        {
            cout << "AF_INET";
        } 
        else if (AF_INET6 == p->ai_family)
        {
            cout << "AF_INET6";
        }
        else
        {
            cout << p->ai_family;
        }
        cout << endl;

        cout << "ai_socktype: ";
        if (SOCK_STREAM == p->ai_socktype)
        {
            cout << "SOCK_STREAM";
        } 
        else if (SOCK_DGRAM == p->ai_socktype)
        {
            cout << "SOCK_DGRAM";
        }
        else if (SOCK_SEQPACKET == p->ai_socktype)
        {
            cout << "SOCK_SEQPACKET";
        }
        else
        {
            cout << p->ai_socktype;
        }
        cout << endl;

        cout << "ai_protocol: ";
        if (IPPROTO_TCP == p->ai_protocol)
        {
            cout << "IPPROTO_TCP";
        } 
        else if (IPPROTO_UDP == p->ai_protocol)
        {
            cout << "IPPROTO_UDP";
        }
        else if (IPPROTO_SCTP == p->ai_protocol)
        {
            cout << "IPPROTO_SCTP";
        }
        else
        {
            cout << p->ai_protocol;
        }
        cout << endl;

        cout << "ai_addrlen: " << p->ai_addrlen << endl;
        if (p->ai_canonname)
        {
            cout << "ai_canonname: " << p->ai_canonname << endl;
        }
        if (p->ai_addr)
        {
            if (AF_INET == p->ai_family && inet_ntop(p->ai_family, &((struct sockaddr_in*)p->ai_addr)->sin_addr, buf, sizeof(buf)))
            {
                cout << "address: " << buf << endl;
            }
            else if (AF_INET6 == p->ai_family && inet_ntop(p->ai_family, &((struct sockaddr_in6*)p->ai_addr)->sin6_addr, buf, sizeof(buf)))
            {
                cout << "address: " << buf << endl;
            }
        }
        cout << endl;
    }

    freeaddrinfo(res);








    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    inet_pton(AF_INET, "172.173.1.1", &addr.sin_addr);
    
    char hostbuf[1024];
    bzero(hostbuf, sizeof(hostbuf));
    char portbuf[1024];
    bzero(portbuf, sizeof(portbuf));
    ret = getnameinfo((struct sockaddr*)&addr, sizeof(addr), hostbuf, sizeof(hostbuf), portbuf, sizeof(portbuf), NI_NAMEREQD);
    if (ret != 0)
    {
        cout << "getnameinfo failed: " << gai_strerror(ret) << endl;
        return ret;
    }
    cout << "host: " << hostbuf << endl;
    cout << "port: " << portbuf << endl;

    return 0;
}


