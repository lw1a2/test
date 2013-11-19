#include <pcap/pcap.h>
#include <strings.h>
#include <iostream>

using namespace std;

int main()
{
    char errbuf[PCAP_ERRBUF_SIZE];
    bzero(errbuf, sizeof(errbuf));
    char *dev = pcap_lookupdev(errbuf);
    if (NULL == dev)
    {
        cout << "pcap_lookupdev failed: " << errbuf << endl;
        return 1;
    }
    else
    {
        cout << dev << endl;
    }

    pcap_t *pd = pcap_open_live(dev, 200, 1, 500, errbuf);
    if (NULL == pd)
    {
        cout << "pcap_open_live failed: " << errbuf << endl;
        return 1;
    }

//  bpf_u_int32 ip;
//  bpf_u_int32 mask;
//  int ret = pcap_lookupnet(dev, &ip, &mask, errbuf);
//  if (ret != 0)
//  {
//      cout << "pcap_lookupnet failed: " << errbuf << endl;
//      return 1;
//  }

    struct pcap_pkthdr h;
    const u_char * p = pcap_next(pd, &h);
    if (NULL == p)
    {
        cout << "pcap_next failed: " << endl;
        return 1;
    }
    else
    {
        cout << p << endl;
    }

    return 0;
}
