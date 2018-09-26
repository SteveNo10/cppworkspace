/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-26
* Descript: 
*
============================================================================*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

char cmdp[] = "echo";
char cmd1[] = "/usr/bin/echo";
char arg1[] = "hello";
char arg2[] = "world";

void f_execl()
{
    printf("execl\n");
    if(-1 == execl(cmd1, cmd1, arg1, arg2, NULL))
    {
        printf("execl err:%m\n");
    }
}

void f_execlp()
{
    printf("execlp\n");
    if(-1 == execlp(cmdp, cmdp, arg1, arg2, NULL))
    {
        printf("execl err:%m\n");
    }
}

void f_execv()
{
    printf("execv\n");
    char* argv[] = {cmd1, arg1, arg2, NULL};
    if(-1 == execv(cmd1, argv))
    {
        printf("execv err:%m\n");
    }
}

int main(int, char**)
{
    pid_t pid = fork();
    if(-1 == pid)
    {
        printf("fork err:%m\n");
        return -1;
    }
    else if(0 == pid)
    {
        f_execl();
        _exit(0);
    }
    
    waitpid(pid, NULL, 0);

    pid = fork();
    if(-1 == pid)
    {
        printf("fork err:%m\n");
        return -1;
    }    
    else if(0 == pid)
    {
        f_execv();
        _exit(0);
    }

    waitpid(pid, NULL, 0);

    pid = fork();
    if(-1 == pid)
    {
        printf("fork err:%m\n");
        return -1;
    }
    else if(0 == pid)
    {
        f_execlp();
        _exit(0);
    }

    waitpid(pid, NULL, 0);

    printf("parent\n");
}
