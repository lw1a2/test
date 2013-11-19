#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <net/if.h>

using namespace std;

int main()
{
    int ret = 0;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sock)
    {
        perror("socket");
        return errno;
    }

    int on = 1;
    ret = setsockopt(sock, IPPROTO_IP, IP_PKTINFO, &on, sizeof(on));
    if (-1 == ret)
    {
        cout << "setsockopt" << strerror(errno) << endl;
        return errno;
    }

    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(58889); 
//  serv.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_pton(AF_INET, "172.173.1.1", &serv.sin_addr);

    ret = bind(sock, (sockaddr *)&serv, sizeof(serv));
    if (-1 == ret)
    {
        perror("bind");
        return errno;
    }

    struct sockaddr_in cli;
    bzero(&cli, sizeof(cli));
    socklen_t len = sizeof(cli);
    char buf[10240];

    while (1)
    {
        bzero(buf, sizeof(buf));
        struct msghdr msg;
        bzero(&msg, sizeof(msg));
        struct iovec iov;
        bzero(&iov, sizeof(iov));
        struct cmsghdr cmsg;
        bzero(&cmsg, sizeof(cmsg)); 
        char cmbuf[1024];
        bzero(cmbuf, sizeof(cmbuf)); 
        iov.iov_base = buf;
        iov.iov_len = sizeof(buf);
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_name = &cli;
        msg.msg_namelen = sizeof(cli);
        msg.msg_control = cmbuf;
        msg.msg_controllen = sizeof(cmbuf);
        int n = recvmsg(sock, &msg, 0);
        if (-1 == n)
        {
            perror("recvmsg");
            return errno;
        }

        char addr_buf[INET_ADDRSTRLEN];
        bzero(addr_buf, sizeof(addr_buf));
        if (inet_ntop(AF_INET, &cli.sin_addr, addr_buf, sizeof(addr_buf)))
        {
            printf("%s.%d", addr_buf, ntohs(cli.sin_port));
        }

        for (struct cmsghdr *p = CMSG_FIRSTHDR(&msg);
             p != NULL; p = CMSG_NXTHDR(&msg, p))
        {

            if (IPPROTO_IP == p->cmsg_level && IP_PKTINFO == p->cmsg_type)
            {
                struct in_pktinfo *pktinfo;
                bzero(&pktinfo, sizeof(pktinfo));
                pktinfo = (struct in_pktinfo *)&CMSG_DATA(p);
                char ifbuf[10];
                bzero(ifbuf, sizeof(ifbuf));
                cout << " (" << if_indextoname(pktinfo->ipi_ifindex, ifbuf) << ")";
            }

        }

        printf(" %s\n", buf);

       
    }

    return 0; 
}
    