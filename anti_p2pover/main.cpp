#include <string.h>
#include <pcap.h>
#include <iostream>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

char errbuf[PCAP_ERRBUF_SIZE];

int main()
{
    int ret = -1;

    char *devic = pcap_lookupdev(errbuf);
    if (devic != NULL)
    {
        cout << devic << endl;
    }
    else
    {
        cout << errbuf << endl;
        return errno;
    }

    pcap_t *fd = pcap_open_live(devic, 200, 0, 500, errbuf);
    if (fd == NULL)
    {
        cout << errbuf << endl;
        return errno;
    }

    bpf_u_int32 localnet = 0, netmask = 0;
    ret = pcap_lookupnet(devic, &localnet, &netmask, errbuf);
    if (ret == -1)
    {
        cout << errbuf << endl;
        return errno;
    }
    else
    {
        char str[20];
        memset(str, 0, 20);
        cout << "localnet: " << inet_ntop(AF_INET, &localnet, str, 20) << endl;
        memset(str, 0, 20);
        cout << "netmask: " << inet_ntop(AF_INET, &netmask, str, 20) << endl;
    }

    return 0;
}

