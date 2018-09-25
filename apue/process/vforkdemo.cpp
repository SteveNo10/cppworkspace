/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-25
* Descript: 
*
* 1.vfork后子进程运行完父进程才会运行
* 2.子进程需要调用_exit或exit冲洗标准I/O流，否则输出异常
============================================================================*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int, char**)
{
    int a = 0;
    
    pid_t pid = vfork();
    if(-1 == pid)
    {
        printf("vfork err:%m\n");
        return -1;
    }
    else if(0 == pid)
    {
        a++;
        printf("child a:%d\n", a);
        _exit(0);
    }
    else
    {
        waitpid(pid, NULL, 0);
        printf("parent a:%d\n", a);
    }

    return 0;
}
