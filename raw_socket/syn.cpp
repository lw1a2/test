#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


/* IP HEADER
 * Taken from glibc 2.2, and modified
 */
typedef struct {
#if __BYTE_ORDER == __LITTLE_ENDIAN
    unsigned int header_len:4;
    unsigned int version:4;
#elif __BYTE_ORDER == __BIG_ENDIAN
    unsigned int version:4;
    unsigned int header_len:4;
#else
#error "Please fix <bits/endian.h>"
#endif
    u_int8_t tos;
    u_int16_t tot_len;
    u_int16_t id;
#if __BYTE_ORDER == __LITTLE_ENDIAN
    u_int16_t frag_off1:5;
    u_int16_t mf:1;
    u_int16_t df:1;
    u_int16_t res:1;
    u_int16_t frag_off2:8;
#define IP_SET_FRAGOFF(ip,v) {(ip)->frag_off1=((v)&0x1F00)>>8;(ip)->frag_off2=(v)&0x00FF;}
#elif __BYTE_ORDER == __BIG_ENDIAN
    u_int16_t res:1;
    u_int16_t df:1;
    u_int16_t mf:1;
    u_int16_t frag_off:13;
#define IP_SET_FRAGOFF(ip,v) (ip)->frag_off=(v)
#else
#error "Please fix <bits/endian.h>"
#endif
    u_int8_t ttl;
    u_int8_t protocol;
    u_int16_t check;
    u_int32_t saddr;
    u_int32_t daddr;
} ip_header;

/* TCP HEADER
 * Ripped straight out of glibc-2.2.2, modified for RFC22481
 * Reproduced here to prevent nasty #defines on non-linux boxes
 */
typedef struct {
    u_int16_t source;
    u_int16_t dest;
    u_int32_t seq;
    u_int32_t ack_seq;
#if __BYTE_ORDER == __LITTLE_ENDIAN
    u_int16_t res:4;
    u_int16_t off:4;
    u_int16_t fin:1;
    u_int16_t syn:1;
    u_int16_t rst:1;
    u_int16_t psh:1;
    u_int16_t ack:1;
    u_int16_t urg:1;
    u_int16_t cwr:1;
    u_int16_t ecn:1;
#elif __BYTE_ORDER == __BIG_ENDIAN
    u_int16_t off:4;
    u_int16_t res:4;
    u_int16_t ecn:1;
    u_int16_t cwr:1;
    u_int16_t urg:1;
    u_int16_t ack:1;
    u_int16_t psh:1;
    u_int16_t rst:1;
    u_int16_t syn:1;
    u_int16_t fin:1;
#else
#error "Adjust your <bits/endian.h> defines"
#endif
    u_int16_t window;
    u_int16_t check;
    u_int16_t urg_ptr;
} tcp_header;

/* Checksum a block of data */
uint16_t cksum(uint16_t *packet, int packlen) {
    register unsigned long sum = 0;

    while (packlen > 1) {
        sum += *packet++;
        packlen -= 2;
    }

    if (packlen > 0) {
        sum += *(unsigned char *)packet;
    }

/* TODO: this depends on byte order */
    while (sum >> 16) {
        sum = (sum & 0xffff) + (sum >> 16);
    }

    return (uint16_t)~sum;
}

void tcp_cksum(ip_header *iph, tcp_header *tcph) {
    uint8_t *buf = NULL;
    uint16_t segment_len = ntohs(iph->tot_len) - iph->header_len * 4;
    buf = (uint8_t*)malloc(12 + segment_len);
    if (!buf) {
        fprintf(stderr, "Out of memory: TCP checksum!\n");
        return;
    }

    memcpy(buf, &(iph->saddr), sizeof(uint32_t));
    memcpy(buf + 4, &(iph->daddr), sizeof(uint32_t));
    buf[8] = 0;
    buf[9] = iph->protocol;
    buf[10] = (segment_len & 0xFF00) >> 8;
    buf[11] = (segment_len & 0x00FF);
    memcpy(buf + 12, tcph, segment_len);
    tcph->check = cksum((uint16_t * )buf, (uint16_t)12 + segment_len);

    free(buf);

    return;
}

void ip_cksum(ip_header *iph) {
    iph->check = cksum((uint16_t * )iph, iph->header_len * 4);
}

void build_syn(char * buf)
{
    ip_header iph;
    tcp_header tcph;
    int ret = 0;

    /* Initialize IP header */
    bzero(&iph, sizeof(iph));
    iph.version = 4;
    iph.header_len = 5;
    iph.tot_len = htons(40);
    iph.ttl = 255;
    iph.protocol = 6;
    ret = inet_pton(AF_INET, "10.1.1.1", &iph.saddr);
    if (ret != 1) {
        printf("inet_pton 10.1.1.1 error");
        return;
    }
    ret = inet_pton(AF_INET, "10.16.1.2", &iph.daddr);
    if (ret != 1) {
        printf("inet_pton 10.16.1.2 error");
        return;
    }
    ip_cksum(&iph);
    memcpy(buf, (char *)&iph, sizeof(ip_header));

    /* Initialize TCP header */
    bzero(&tcph, sizeof(tcp_header));
    tcph.source = htons(58888);
    tcph.dest = htons(8888);
    tcph.seq = htonl(time(NULL));
    tcph.off = 5;
    tcph.syn = 1;
    tcph.window = htons((u_int16_t)65535);
    tcp_cksum(&iph, &tcph);
    memcpy(buf + sizeof(ip_header), (char *)&tcph, sizeof(tcp_header));

    return;
}


int main()
{
    int ret = 0;
    int sock_out = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (-1 == sock_out) {
        perror("socket output");
        return errno;
    }
    const int on = 1;
    ret = setsockopt(sock_out, IPPROTO_IP, IP_HDRINCL, (const void *)&on, sizeof(on));
    if (-1 == ret) {
        perror("setsockopt IP_HDRINCL");
        return errno;
    }

    char buf[40];
    bzero(buf, sizeof(buf));
    build_syn(buf);

    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    ret = inet_pton(AF_INET, "10.16.1.2", &addr.sin_addr);
    if (ret != 1) {
        printf("inet_pton 10.16.1.2 error");
        return 1;
    }

    ret = sendto(sock_out, buf, sizeof(buf), 0, (struct sockaddr*)&addr, sizeof(addr));
    if (-1 == ret) {
        perror("sendto");
        return errno;
    }

    return 0;
}
