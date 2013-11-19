#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <errno.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

u_short
in_cksum(const u_short *addr, register int len, u_short csum)
{
	register int nleft = len;
	const u_short *w = addr;
	register u_short answer;
	register int sum = csum;

	/*
	 *  Our algorithm is simple, using a 32 bit accumulator (sum),
	 *  we add sequential 16 bit words to it, and at the end, fold
	 *  back all the carry bits from the top 16 bits into the lower
	 *  16 bits.
	 */
	while (nleft > 1)  {
		sum += *w++;
		nleft -= 2;
	}

	/* mop up an odd byte, if necessary */
	if (nleft == 1)
		sum += htons(*(u_char *)w << 8);

	/*
	 * add back carry outs from top 16 bits to low 16 bits
	 */
	sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
	sum += (sum >> 16);			/* add carry */
	answer = ~sum;				/* truncate to 16 bits */
	return (answer);
}

int count;

void sig_alarm(int)
{
    int ret = 0;
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (-1 == sock)
    {
        perror("socket");
        return;
    }

    struct sockaddr_in peer;
    bzero(&peer, sizeof(peer));
    peer.sin_family = AF_INET;
    ret = inet_pton(AF_INET, "172.173.1.102", &peer.sin_addr);
    if (ret != 1)
    {
        printf("inet_pton failed\n");
        return;
    }

    int n = 0;
    struct icmp request;
    bzero(&request, sizeof(request));
    request.icmp_code = 0;
    request.icmp_type = ICMP_ECHO;
    request.icmp_id = getpid() & 0xffff;
    request.icmp_seq = count++;
    request.icmp_cksum = in_cksum((u_short * ) & request, 8, 0);

    n = sendto(sock, &request, 8, 0, (struct sockaddr *)&peer, sizeof(peer));
    if (-1 == n)
    {
        perror("sendto");
        return;
    }

    alarm(1);
}

int main()
{
    int ret = 0;

    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sa.sa_handler = sig_alarm;

    ret = sigaction(SIGALRM, &sa, NULL);
    if (-1 == ret)
    {
        perror("sigaction");
        return errno;
    }

    sig_alarm(1);

    while (1)
    {
        int ret = 0;
        int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
        if (-1 == sock)
        {
            perror("socket");
            return errno;
        }

        struct sockaddr_in peer;
        bzero(&peer, sizeof(peer));
        peer.sin_family = AF_INET;
        ret = inet_pton(AF_INET, "172.173.1.102", &peer.sin_addr);
        if (ret != 1)
        {
            printf("inet_pton failed\n");
            return 1;
        }

        int n = 0;
        unsigned char buf[1024];
        bzero(buf, sizeof(buf));

        socklen_t len = 0;
        n = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&peer, &len);
        if (-1 == n)
        {
            if (EINTR == errno)
            {
                continue;
            }
            else
            {
                perror("recvfrom");
                return errno;
            }
        }

    }

    return 0;
}
