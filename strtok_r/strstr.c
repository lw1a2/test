#include <string.h>
#include <stdio.h>

int main() 
{
    char fname[1024];
    char *end = NULL;
    int count = 0;
    char *p = " Accept-Encoding: gzip, deflate\r\nDNT: 1\r\nConnection: keep-alive\r\n\r\nGET /index.html HTTP/1.1\r\nHost: 10.3.1.100\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:27.0) Gecko/20100101 Firefox/27.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3\r\nAccept-Encoding: gzip, deflate\r\nDNT: 1\r\nConnection: keep-alive\r\n\r\nGET /index.html HTTP/1.1\r\nHost: 10.3.1.100\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:27.0) Gecko/20100101 Firefox/27.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3\r\nCan't parse and get file name from Get header: Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3\r\nAccept-Encoding: gzip, deflate\r\nDNT: 1\r\nConnection: keep-alive\r\n\r\nGET /index.html HTTP/1.1\r\nHost: 10.3.1.100\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:27.0) Gecko/20100101 Firefox/27.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3\r\nAccept-Encoding: gzip, deflate\r\nDNT: 1\r\nConnection: keep-alive\r\n\r\n";
    memset(fname, 0, 1024);

    while (1) {
        if (strlen(fname) == 0) {
            sscanf(p, "GET /%s HTTP/1.1", fname);
            printf("fname: %s\n", fname);
        }
        end = strstr(p, "\r\n\r\n");
        if (end != NULL) {
            count += 1;
            p = end + strlen("\r\n\r\n");
        } else {
            break;
        }
    }

    printf("count: %d\n", count);

    return 0;
}