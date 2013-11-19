//������ʵ���ڵ��߳���ͬʱ�����ڲ���Ϣ��socket
//��pthread_kill���̷߳���SIGUSR1��ģ���ڲ���Ϣ����
//��stdin��ģ��socket
#include <pthread.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/select.h>
#include <cstdio>
#include <errno.h>
#include <signal.h>

using namespace std;

void* work(void* arg)
{
    int ret = 0;
    ret = pthread_detach(pthread_self());
    if (ret != 0)
    {
        cout << "pthread_detach: " << strerror(ret) << endl;
        exit(ret);
    }

    //�ڴ��߳���ʹ��select����socket
    int sockfd = *(int*)arg;
    fd_set rset, rs;
    FD_ZERO(&rset);
    FD_SET(sockfd, &rset);

    while (1)
    {
        rs = rset;
        ret = select(sockfd + 1, &rs, NULL, NULL, NULL);
        if (-1 == ret)
        {
            if (EINTR == errno)
            {
                continue;
            }
            else
            {
                perror("select");
                exit(errno);
            }
        }

        char buf[4096];
        bzero(buf, sizeof(buf));
        int n;
        while (n = read(sockfd, buf, sizeof(buf)))
        {
            if (-1 == n)
            {
                if (EINTR == errno)
                {
                    continue;
                }
                else
                {
                    perror("read");
                    exit(errno);
                }
            }

            cout << buf;
            bzero(buf, sizeof(buf));
        }

        cout << endl;
    }

    return NULL;
}

void sig_usr1(int signo)
{
    cout << "receive internal message " << endl;
}

int main()
{
    int ret = 0;
    pthread_t thread_id;
    int sockfd = STDIN_FILENO;
    ret = pthread_create(&thread_id, NULL, work, &sockfd);
    if (ret != 0)
    {
        cout << "pthread_create: " << strerror(ret) << endl;
        exit(ret);
    }

    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sa.sa_handler = sig_usr1;
    ret = sigaction(SIGUSR1, &sa, NULL);
    if (-1 == ret)
    {
        perror("sigaction");
        exit(errno);
    }

    while (1)
    {
        //ÿ3�뷢��һ���ڲ���Ϣ
        sleep(3);
        pthread_kill(thread_id, SIGUSR1);
    }

    return 0;
}

