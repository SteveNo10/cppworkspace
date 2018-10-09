/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-29
* Descript: 
*
*  1-31 非实时信号。阻塞后仅传递一次，无序
* 32-64 实时信号。传递多次，有序，优先传递信号编号小的
*
* 1) SIGHUP         Term    用户终端连接断开时，通知同一session内各个作业
*                           针对守护进程，常用于通知再次读取配置文件
* 2) SIGINT         Term    Ctrl-C
* 3) SIGQUIT        Core    Ctrl-\
* 4) SIGILL         Core    执行非法指令
* 5) SIGTRAP        Core    由断点指令或其它trap指令产生. 由debugger使用
* 6) SIGABRT        Core    abort
* 7) SIGBUS         Core    非法地址，如mmap访问大于文件大小的地址
* 8) SIGFPE         Core    算术异常，如除以0、浮点溢出等
* 9) SIGKILL        Term    不能被捕捉和忽略，杀死进程的可靠方法
* 10) SIGUSR1       Term    自定义
* 11) SIGSEGV       Core    无效内存引用，如访问未经初始化的指针、往没有写权限的内存写数据
* 12) SIGUSR2       Term    自定义
* 13) SIGPIPE       Term    写管道时读管道没打开或终止、写Socket时读Socket未打开或关闭
* 14) SIGALRM       Term    alarm
* 15) SIGTERM       Term    kill(1)默认发送此信号，但是可阻塞可忽略，不行才用SIGKILL
* 16) SIGSTKFLT     Term    未用
* 17) SIGCHLD       Ign     子进程结束，父进程收到此信号
* 18) SIGCONT       Cont    让停止的进程继续执行，不能被阻塞
* 19) SIGSTOP       Stop    停止进程执行，不能被阻塞或处理或忽略
* 20) SIGTSTP       Stop    Ctrl-Z
* 21) SIGTTIN       Stop    后台进程组试图读控制终端时，终端驱动程序产生此信号
* 22) SIGTTOU       Stop    后台进程组试图写控制终端时，终端驱动程序产生此信号
* 23) SIGURG        Ign     有紧急数据或者out-of-band数据到达socket时产生
* 24) SIGXCPU       Core    超过CPU时间资源限制
* 25) SIGXFSZ       Core    超过文件长度限制
* 26) SIGVTALRM     Term    settimer(2)虚拟间隔时间已经超时时
* 27) SIGPROF       Term    settimer(2)设置的profiling interval timer超时时
* 28) SIGWINCH      Ign     ioctl设置窗口大小改变时，发送至前台进程组
* 29) SIGIO         Term    异步IO事件
* 30) SIGPWR        Term    电压过低，一般发送给init进程，处理停机操作
* 31) SIGSYS        Term    非法系统调用。如旧操作系统运行不支持的新操作系统可执行代码时
* 
* 34) SIGRTMIN
* ...
* 64) SIGTRMAX
*
* signal    执行过一次后会恢复为默认SIG_DFL。重新注册时中间有空档期，此时有信号可能会异常
* sigaction 推荐使用，复杂但是全面
============================================================================*/

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

void f_sighandle(int signo)
{
    printf("signal receive signo:%d\n", signo);
    signal(SIGINT, f_sighandle);
}

void f_sigachandle(int signo)
{
    printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx sigaction receive signo:%d\n", signo);
    // sleep(5);
}

void f_siglog(int signo)
{
    int fd = open("./signal.log", O_CREAT|O_RDWR|O_TRUNC, 0664);
    if(-1 == fd)
    {
        perror("open err");
        return;
    }

    char buf[BUFSIZ] = {0};
    time_t now = time(NULL);
    char timebuf[BUFSIZ] = {0};
    ctime_r(&now, timebuf);
    int size = snprintf(buf, BUFSIZ, "%s get sig:%d\n", timebuf, signo);
    write(fd, buf, size);
    close(fd);
}

int main(int, char**)
{
    struct sigaction act_log;
    act_log.sa_handler = f_siglog;
    sigemptyset(&act_log.sa_mask);
    act_log.sa_flags = 0;
    sigaction(SIGHUP, &act_log, NULL);
    printf("close this session will write to signal.log, but here raise(SIGHUP)\n");
    raise(SIGHUP);

    struct sigaction act;
    act.sa_handler = f_sigachandle;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT);
    sigaddset(&act.sa_mask, SIGINT);
    sigaddset(&act.sa_mask, SIGABRT);
    act.sa_flags = 0;

    sigaction(SIGINT, &act, NULL);
    printf("input Ctrl+C\n");
    pause();

/*     signal(SIGINT, f_sighandle); */

    sigaction(SIGQUIT, &act, NULL);
    printf("input Ctrl+\\\n");
    pause();

    sigaction(SIGALRM, &act, NULL);
    printf("alarm\n");
    alarm(1);
    pause();

    sigaction(SIGTERM, &act, NULL);
    printf("input kill %d ! kill default send this signal\n", getpid());
    pause();

    sigaction(SIGCHLD, &act, NULL);
    printf("child stopped or terminated\n");
    pid_t pid = fork();
    if(-1 == pid)
    {
        perror("fork err");
        return -1;
    }
    else if(0 == pid)
    {
        sleep(3);
        exit(0);
    }

    pause();

    sigaction(SIGTSTP, &act, NULL);
    printf("input Ctrl+Z\n");
    pause();
    
    sigaction(SIGABRT, &act, NULL);
    printf("abort()\n");
    abort();

    while(true)
    {
        pause();
    }

    return 0;
}
