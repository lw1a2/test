#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string>

using namespace std;

int f(char c)
{
    switch (c)
    {
    case 'a':
    case 'A':
        return 10;
    case 'b':
    case 'B':
        return 11;
    case 'c':
    case 'C':
        return 12;
    case 'd':
    case 'D':
        return 13;
    case 'e':
    case 'E':
        return 14;
    case 'f':
    case 'F':
        return 15;
    default:
        return int(c - 48);
    }
}

int hex2dec(const char* c)
{
    if (c == NULL || c + 1 == NULL)
    {
        return -1;
    }

    return f(c[1]) + f(c[0]) * 16;
}

int main()
{
    int sockfd = -1;
    int ret = -1;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd)
    {
        perror(strerror(errno));
    }

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(80);
    inet_pton(AF_INET, "192.168.1.1", &servaddr.sin_addr);

    ret = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if (-1 == ret)
    {
        perror(strerror(errno));
    }

    int n = -1;
    char prefix[] = "474554202f20485454502f312e310d0a486f73743a203139322e3136382e312e310d0a436f6e6e656374696f6e3a206b6565702d616c6976650d0a";
    //char name_passwd[] = "417574686f72697a6174696f6e3a2042617369632059575274615734364d513d3d0d0a";
    char name_passwd[] = "417574686f72697a6174696f6e3a2042617369632059575274615734364d513d3d0e0a";
    char suffix[] = "557365722d4167656e743a204d6f7a696c6c612f352e30202857696e646f7773204e5420362e313b20574f57363429204170706c655765624b69742f3533352e3220284b48544d4c2c206c696b65204765636b6f29204368726f6d652f31352e302e3837342e313231205361666172692f3533352e320d0a4163636570743a20746578742f68746d6c2c6170706c69636174696f6e2f7868746d6c2b786d6c2c6170706c69636174696f6e2f786d6c3b713d302e392c2a2f2a3b713d302e380d0a4163636570742d456e636f64696e673a20677a69702c6465666c6174652c736463680d0a4163636570742d4c616e67756167653a207a682d434e2c7a683b713d302e380d0a4163636570742d436861727365743a2047424b2c7574662d383b713d302e372c2a3b713d302e330d0a0d0a";
    string s;
    char buf_write[1024];
    memset(buf_write, 0, 1024);
    int j = 0;
    for (int i = 0; i < strlen(prefix); i += 2, ++j)
    {
        s = prefix[i];
        s += prefix[i + 1];
        buf_write[j] = hex2dec(s.c_str());
    }
    for (int i = 0; i < strlen(name_passwd); i += 2, ++j)
    {
        s = name_passwd[i];
        s += name_passwd[i + 1];
        buf_write[j] = hex2dec(s.c_str());
    }
    for (int i = 0; i < strlen(suffix); i += 2, ++j)
    {
        s = suffix[i];
        s += suffix[i + 1];
        buf_write[j] = hex2dec(s.c_str());
    }
    n = write(sockfd, buf_write, j);
    if (-1 == n)
    {
        perror(strerror(errno));
    }

    char buf_read[1024];
    memset(buf_read, 0, 1024);
    while ((n = read(sockfd, buf_read, 1024)) > 0)
    {
        //cout << buf_read;
        if (strncmp(buf_read, "HTTP/1.1 401 N/A", strlen("HTTP/1.1 401 N/A")))
        {
            cout << "Failed" << endl;
        }
        else
        {
            cout << "OK" << endl;
        }
        break;
    }

    return 0;
}

