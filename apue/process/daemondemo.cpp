/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-27
* Descript: 
* 1.umask(0)
* 2.fork-exit-parent
* 3.setsid
* 4.signal(SIGHUP, SIG_IGN)
* 4.chdir("/")
* 5.close all fds
* 6.</dev/null
============================================================================*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <syslog.h>
#include <time.h>
#include <string.h>

void f_daemon()
{
    umask(0);

    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork err");
        exit(1);
    }
    else if(pid > 0)
    {
        exit(0);
    }

    if(-1 == setsid())
    {
        perror("setsid err");
        exit(1);
    }

    if(SIG_ERR == signal(SIGHUP, SIG_IGN))
    {
        perror("signal err");
        exit(1);
    }

    if(-1 == chdir("/"))
    {
        perror("chdir err");
        exit(1);
    }

    struct rlimit rlim;
    if(-1 == getrlimit(RLIMIT_NOFILE, &rlim))
    {
        perror("getrlimit err");
        exit(1);
    }

    if(rlim.rlim_max == RLIM_INFINITY)
    {
        rlim.rlim_max = 1024;
    }
    
    for(rlim_t i = 0; i < rlim.rlim_max; ++i)
    {
        close(i);
    }

    int fd0 = open("/dev/null", O_RDWR);
    int fd1 = dup(fd0);
    int fd2 = dup(fd0);

    if(0 != fd0 || 1 != fd1 || 2 != fd2)
    {
        syslog(LOG_INFO, "err fd0:%d or fd1:%d or fd2:%d", fd0, fd1, fd2);
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s type\n   0:system daemon\n   other:user daemon\n", argv[0]);
        return -1;
    }

    int type = atoi(argv[1]);
    if(0 == type)
    {
        if(-1 == daemon(0, 0))
        {
            perror("daemon err");
            return -1;
        }
    } 
    else
    {
        f_daemon();
    }
    
    char filename[] = "/home/dev/workspace/cppworkspace/apue/process/daemon.log";
    FILE* pFile = fopen(filename, "a+");
    if(NULL == pFile)
    {
        syslog(LOG_INFO, "fopen %s err:%m", filename);
        return -1;
    }

    while(true)
    {
        time_t now = time(NULL);
        char* pTime = ctime(&now);
        if(-1 == fputs(pTime, pFile))
        {
            syslog(LOG_INFO, "fputs fd %s err:%m", ctime(&now));
            return -1;
        }

        fflush(pFile);
        sleep(1);
    }
}
