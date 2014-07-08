#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

#include <asm/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>

int main(int argc, char *argv[])
{
    struct sockaddr_nl saddr, daddr;
    struct nlmsghdr *nlhdr = NULL;
    struct msghdr msg;
    struct iovec iov;
    int sd;
    const char* text_line = "hello";
    int ret = -1;

    printf("pid: %d\n", getpid());

    sd = socket(AF_NETLINK, SOCK_RAW, NETLINK_USERSOCK);
    memset(&saddr, 0, sizeof(saddr));
    memset(&daddr, 0, sizeof(daddr));

    saddr.nl_family = AF_NETLINK;      
    saddr.nl_pid = getpid();
    saddr.nl_groups = 0;
    bind(sd, (struct sockaddr*)&saddr, sizeof(saddr));

    daddr.nl_family = AF_NETLINK;
    daddr.nl_pid = 0;
    daddr.nl_groups = 0;

    nlhdr = (struct nlmsghdr *)malloc(NLMSG_SPACE(1024));
    memcpy(NLMSG_DATA(nlhdr), text_line, strlen(text_line));
    memset(&msg, 0 ,sizeof(struct msghdr));

    nlhdr->nlmsg_len = NLMSG_LENGTH(strlen(text_line));
    nlhdr->nlmsg_pid = getpid();  /* self pid */
    nlhdr->nlmsg_flags = 0;

    iov.iov_base = (void *)nlhdr;
    iov.iov_len = nlhdr->nlmsg_len;
    msg.msg_name = (void *)&daddr;
    msg.msg_namelen = sizeof(daddr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    ret = sendmsg(sd, &msg, 0);
    if (-1 == ret)
    {
        perror("sendmsg");
    }

//  msg.msg_name = (void *)&saddr;
//  ret = recvmsg(sd, &msg, 0);
//  if (ret == -1)
//  {
//      perror("recvmsg");
//  }

    close(sd);
}

