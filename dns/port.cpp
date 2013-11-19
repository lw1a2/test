#include <iostream>
#include <netdb.h>
#include <strings.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

using namespace std;

int main()
{
    struct servent * serv = getservbyname("domain", "udp");
    if (!serv)
    {
        cout << "getservbyname failed: " << hstrerror(h_errno) << endl;
        return 1;
    }

    cout << "canonical name: " << serv->s_name << endl;
    for (char ** pp = serv->s_aliases; *pp != NULL; ++pp)
    {
        cout << "alias: " << *pp << endl;
    }
    cout << "port: " << ntohs(serv->s_port) << endl;
    cout << "protocol: " << serv->s_proto << endl;

    struct servent * serv2 = getservbyport(htons(58888), NULL);
    if (!serv2)
    {
        cout << "getservbyport failed: " << hstrerror(h_errno) << endl;
        return 1;
    }
    cout << "canonical name: " << serv2->s_name << endl;
    for (char ** pp = serv2->s_aliases; *pp != NULL; ++pp)
    {
        cout << "alias: " << *pp << endl;
    }
    cout << "port: " << ntohs(serv2->s_port) << endl;
    cout << "protocol: " << serv2->s_proto << endl;

    return 0;
}


