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

    //1：确保shell命令执行完毕
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

    //2：确保不再有控制终端
    pid = setsid();
    if (-1 == pid)
    {
        perror("setsid");
        return errno;
    }

    //3：忽略SIGHUP。会话头进程终止时，其会话中的所有进程都收到SIGHUP信号
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

    //4：再次fork，确保新的子进程不再是会话头进程，从而不能自动获得控制终端
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

    //5：把工作目录改到根目录
    ret = chdir("/");
    if (-1 == ret)
    {
        perror("chdir");
        return errno;
    }

    //6：关闭所有打开的文件描述符
    for (int i = 0; i < 1024; ++i)
    {
        close(i);
    }

    //7：重定向标准输入、输出、错误到/dev/null
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);

    //8：使用syslogd处理错误
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

