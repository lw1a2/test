#include <string>
#include <sys/socket.h>
#include <iostream>
#include <netdb.h>
#include <cstdlib>
#include <cstdio>
#include <errno.h>
#include <strings.h>
#include <arpa/inet.h>
#include <fstream>
#include <cstring>
#include <fcntl.h>

using namespace std;

typedef struct sockaddr SA;
const int MAXLINE = 4096;
const string output = "output/";

const string GET_CMD = "GET %s HTTP/1.0\r\n\r\n";

void remove_http_header(char** line, const string& header_end, int& n)
{
    char* pos = strstr(*line, header_end.c_str());
    if (pos != NULL)
    {
        pos += header_end.size();
        char line_removed_header[MAXLINE];
        bzero(line_removed_header, sizeof(line_removed_header));
        n -= pos - *line;
        bcopy(pos, line_removed_header, n);
        bzero(*line, MAXLINE);
        bcopy(line_removed_header, *line, n);
    }
}

void home_page(const string& host)
{
    int ret = 0;
    string serv = "80";

    struct addrinfo *servaddr = NULL;
    struct addrinfo hints;
    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    ret = getaddrinfo(host.c_str(), serv.c_str(), &hints, &servaddr);
    if (ret != 0)
    {
        cout << gai_strerror(ret) << endl;
        freeaddrinfo(servaddr);
        exit(ret);
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd)
    {
        perror("socket");
        freeaddrinfo(servaddr);
        exit(errno);
    }

    ret = connect(sockfd, (SA*)servaddr->ai_addr, servaddr->ai_addrlen);
    if (-1 == ret)
    {
        perror("connect");
        freeaddrinfo(servaddr);
        exit(errno);
    }

    freeaddrinfo(servaddr);

    //主页
    char line[MAXLINE];
    bzero(line, sizeof(line));
    int n = snprintf(line, sizeof(line), GET_CMD.c_str(), "/");
    n = write(sockfd, line, n);
    if (-1 == n)
    {
        perror("write");
        exit(errno);
    }

    bzero(line, sizeof(line));
    string filename = output + "index.html";
    ofstream homepage(filename.c_str());
    bool header = true;
    while ((n = read(sockfd, line, sizeof(line))) > 0)
    {
        //去掉多余的开头
        if (header)
        {
            char* tmp = (char*)line;
            remove_http_header(&tmp, "Connection: Close\r\n\r\n", n);
            header = false;
        }
        homepage << line;
        bzero(line, sizeof(line));
    }
}

void start_connect(const string& host, const string& file)
{
    //GIF文件
    int ret = 0;
    string serv = "80";

    struct addrinfo *servaddr = NULL;
    struct addrinfo hints;
    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    ret = getaddrinfo(host.c_str(), serv.c_str(), &hints, &servaddr);
    if (ret != 0)
    {
        cout << gai_strerror(ret) << endl;
        freeaddrinfo(servaddr);
        exit(ret);
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd)
    {
        perror("socket");
        freeaddrinfo(servaddr);
        exit(errno);
    }

    int flag = 0;
    ret = fcntl(sockfd, F_GETFL, flag);
    if (-1 == ret)
    {
        perror("fcntl");
        freeaddrinfo(servaddr);
        exit(errno);
    }
    ret = fcntl(sockfd, F_SETFL, flag | O_NONBLOCK);
    if (-1 == ret)
    {
        perror("fcntl");
        freeaddrinfo(servaddr);
        exit(errno);
    }

    ret = connect(sockfd, (SA*)servaddr->ai_addr, servaddr->ai_addrlen);
    if (-1 == ret)
    {
        if (errno != EINPROGRESS)
        {
            perror("connect");
            freeaddrinfo(servaddr);
            exit(errno);
        }
    }

    freeaddrinfo(servaddr);

    fd_set rset, wset;
    FD_ZERO(&rset);
    FD_SET(sockfd, &rset);
    wset = rset;

    int n = select(sockfd + 1, &rset, &wset, NULL, NULL);
    if (-1 == n)
    {
        perror("select");
        exit(errno);
    }
    int error = 0;
    socklen_t error_len = sizeof(error);
    ret = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &error_len);
    if (-1 == ret)
    {
        perror("getsockopt");
        exit(errno);
    }
    if (error != 0)
    {
        errno = error;
        perror("connect");
        exit(errno);
    }

    ret = fcntl(sockfd, F_SETFL, flag);
    if (-1 == ret)
    {
        perror("fcntl");
        exit(errno);
    }

    char line[MAXLINE];
    bzero(line, sizeof(line));
    n = snprintf(line, sizeof(line), GET_CMD.c_str(), file.c_str());
    n = write(sockfd, line, n);
    if (-1 == n)
    {
        perror("write");
        exit(errno);
    }

    //处理文件名，去掉路径
    string filename;
    string::size_type pos = file.rfind('/');
    if (pos != string::npos)
    {
        filename = file.substr(pos + 1);
    }
    else
    {
        filename = file;
    }
    bzero(line, sizeof(line));
    
    filename = output + filename;
    ofstream gif(filename.c_str());
    bool header = true;
    while ((n = read(sockfd, line, sizeof(line))) > 0)
    {
        //去掉多余的开头
        if (header)
        {
            char* tmp = (char*)line;
            remove_http_header(&tmp, "Content-Type: image/gif\r\n\r\n", n);
            header = false;
        }
        gif.write(line, n);
        bzero(line, sizeof(line));
    }
}

int main()
{
    home_page("www.baidu.com");

    start_connect("www.baidu.com", "/img/baidu_jgylogo3.gif");

    return 0;
}
