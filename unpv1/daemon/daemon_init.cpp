#include <unistd.h>
#include <cstdio>
#include <errno.h>
#include <cstdlib>
#include <syslog.h>
#include <signal.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

int daemon_init(const char* pname, int facility)
{
    //0:umask
    umask(0);

    //1��ȷ��shell����ִ�����
    pid_t pid = fork();
    if (-1 == pid)
    {
        perror("fork 1");
        return errno;
    }
    else if (pid > 0)   //parent
    {
        exit(0);
    }

    //2��ȷ�������п����ն�
    pid = setsid();
    if (-1 == pid)
    {
        perror("setsid");
        return errno;
    }

    //3������SIGHUP���Ựͷ������ֹʱ����Ự�е����н��̶��յ�SIGHUP�ź�
    struct sigaction sa;
    bzero(&sa, sizeof(sa));
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SIG_IGN;
    int ret = sigaction(SIGHUP, &sa, NULL);
    if (-1 == ret)
    {
        perror("sigaction");
        return errno;
    }

    //4���ٴ�fork��ȷ���µ��ӽ��̲����ǻỰͷ���̣��Ӷ������Զ���ÿ����ն�
    pid = fork();
    if (-1 == pid)
    {
        perror("fork 2");
        return errno;
    }
    else if (pid > 0)   //parent
    {
        exit(0);
    }

    //5���ѹ���Ŀ¼�ĵ���Ŀ¼
    ret = chdir("/");
    if (-1 == ret)
    {
        perror("chdir");
        return errno;
    }

    //6���ر����д򿪵��ļ�������
    for (int i = 0; i < 1024; ++i)
    {
        close(i);
    }

    //7���ض����׼���롢���������/dev/null
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);

    //8��ʹ��syslogd�������
    open(pname, LOG_PID, facility);

    return 0;
}

int main(int argc, char* argv[])
{
    daemon_init(argv[0], LOG_USER);

    syslog(LOG_INFO|LOG_USER, "start my daemon");

    while (1)
    {
    }
    return 0;
}

