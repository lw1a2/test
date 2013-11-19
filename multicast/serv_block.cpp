#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <net/if.h>
#include <iostream>

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

    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8888);
//  serv.sin_addr.s_addr = htonl(INADDR_ANY);
    if (inet_pton(AF_INET, "224.0.0.88", &serv.sin_addr) != 1)
    {
        cout << "inet_pton failed" << endl;
        return 1;
    }

//  //using IP_ADD_MEMBERSHIP
//  struct ip_mreq multicast;
//  bzero(&multicast, sizeof(multicast));
//  if (inet_pton(AF_INET, "172.173.1.1", &multicast.imr_interface) != 1)
//  {
//      cout << "inet_pton failed" << endl;
//      return 1;
//  }
//  if (inet_pton(AF_INET, "224.0.0.88", &multicast.imr_multiaddr) != 1)
//  {
//      cout << "inet_pton failed" << endl;
//      return 1;
//  }
//  ret = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicast, sizeof(multicast));
//  if (-1 == ret)
//  {
//      perror("setsockopt");
//      return errno;
//  }

    //using MCAST_JOIN_GROUP
    struct group_req multicast;
    bzero(&multicast, sizeof(multicast));
    multicast.gr_interface = if_nametoindex("eth0");
    memcpy(&multicast.gr_group, &serv, sizeof(serv));
    ret = setsockopt(sock, IPPROTO_IP, MCAST_JOIN_GROUP, &multicast, sizeof(multicast));
    if (-1 == ret)
    {
        perror("setsockopt init to MCAST_JOIN_GROUP");
        return errno;
    }

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

    struct group_source_req multicast_src;
    bzero(&multicast_src, sizeof(multicast_src));
    multicast_src.gsr_group = multicast.gr_group;
    multicast_src.gsr_interface = multicast.gr_interface;
    struct sockaddr_in gsr_source;
    bzero(&gsr_source, sizeof(gsr_source));
    gsr_source.sin_family = AF_INET;
    if (inet_pton(AF_INET, "172.173.1.2", &gsr_source.sin_addr) != 1)
    {
        cout << "inet_pton failed" << endl;
        return 1;
    }
    memcpy(&multicast_src.gsr_source, &gsr_source, sizeof(gsr_source));
    ret = setsockopt(sock, IPPROTO_IP, MCAST_BLOCK_SOURCE, &multicast_src, sizeof(multicast_src));
    if (-1 == ret)
    {
        perror("setsockopt MCAST_BLOCK_SOURCE");
        return errno;
    }

    int i = 0;
    while (1)
    {
        bzero(buf, sizeof(buf));
        int n = recvfrom(sock, buf, sizeof(buf), 0, (sockaddr *)&cli, &len);
        if (-1 == n)
        {
            perror("recvfrom");
            return errno;
        }

        char addr_buf[INET_ADDRSTRLEN];
        bzero(addr_buf, sizeof(addr_buf));
        if (inet_ntop(AF_INET, &cli.sin_addr, addr_buf, sizeof(addr_buf)))
        {
            printf("%s.%d: ", addr_buf, ntohs(cli.sin_port));
        }
        printf("%s\n", buf);

//      ret = setsockopt(sock, IPPROTO_IP, MCAST_LEAVE_GROUP, &multicast, sizeof(multicast));
//      if (-1 == ret)
//      {
//          perror("setsockopt MCAST_LEAVE_GROUP");
//          return errno;
//      }
        ++i;
        if (2 == i)
        {
            ret = setsockopt(sock, IPPROTO_IP, MCAST_UNBLOCK_SOURCE, &multicast_src, sizeof(multicast_src));
            if (-1 == ret)
            {
                perror("setsockopt MCAST_UNBLOCK_SOURCE");
                return errno;
            }
        }
    }

    return 0;
}

