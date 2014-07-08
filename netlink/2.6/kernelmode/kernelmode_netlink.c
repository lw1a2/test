#include <linux/kernel.h>
#include <linux/module.h>

#include <net/sock.h>
#include <net/netlink.h>

static struct sock *netlink_sock;

static void netlink_rcv_msg(struct sk_buff *skb)
{
    struct nlmsghdr *nlh = nlmsg_hdr(skb);
    char *data = NLMSG_DATA(nlh);
    printk("sender's pid: %d\n", nlh->nlmsg_pid);
    printk("%s\n", data);

//  strncpy(NLMSG_DATA(nlh), "word", strlen("word"));
//  nlmsg_unicast(netlink_sock, skb, nlh->nlmsg_pid);
}

static int netlink_init(void)
{
    netlink_sock = netlink_kernel_create(&init_net, NETLINK_USERSOCK, 0,
                                         netlink_rcv_msg, NULL, THIS_MODULE);
    if (!netlink_sock)
    {
        printk(KERN_ERR "%s: receive handler registration failed\n", __func__);
        return -ENOMEM;
    }

    return 0;
}

static void netlink_exit(void)
{
    if (netlink_sock)
    {
        netlink_kernel_release(netlink_sock);
    }
}

module_init(netlink_init);
module_exit(netlink_exit);
MODULE_LICENSE("GPL");

