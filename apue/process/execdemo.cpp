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
#include <stdlib.h>

char cmdp1[] = "echo";
char cmdp2[] = "env_demo";
char cmd1[] = "/usr/bin/echo";
char cmd2[] = "/home/dev/workspace/cppworkspace/apue/process/env_demo";

char arg1[] = "hello";
char arg2[] = "world";
char* argv[] = {cmd1, arg1, arg2, NULL};

char env1[] = "AAA=aaa";
char env2[] = "BBB=bbb";
char* envs[] = {env1, env2, NULL};

void f_execl()
{
    printf("%s\n", __FUNCTION__);
    if(-1 == execl(cmd1, cmd1, arg1, arg2, NULL))
    {
        printf("execl err:%m\n");
    }
}

void f_execlp()
{
    printf("%s\n", __FUNCTION__);
    if(-1 == execlp(cmdp1, cmdp1, arg1, arg2, NULL))
    {
        printf("execl err:%m\n");
    }
}

void f_execle()
{
    printf("%s\n", __FUNCTION__);
    if(-1 == execle(cmd2, cmdp2, arg1, arg2, NULL, envs))
    {
        printf("execle err:%m\n");
    }
}

void f_execv()
{
    printf("%s\n", __FUNCTION__);
    if(-1 == execv(cmd1, argv))
    {
        printf("execv err:%m\n");
    }
}

void f_execvp()
{
    printf("%s\n", __FUNCTION__);
    if(-1 == execvp(cmdp1, argv))
    {
        printf("execvp err:%m\n");
    }
}

void f_execvpe()
{
    printf("%s\n", __FUNCTION__);

    setenv("PATH", "/home/dev/workspace/cppworkspace/apue/process", 1);

    if(-1 == execvpe(cmdp2, argv, envs))
    {
        printf("execvpe err:%m\n");
    }
}

void f_system()
{
    printf("%s\n", __FUNCTION__);
    if(-1 == system("date +%s"))
    {
        printf("system err:%m\n");
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
    printf("\n");

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
    printf("\n");

    pid = fork();
    if(-1 == pid)
    {
        printf("fork err:%m\n");
        return -1;
    }
    else if(0 == pid)
    {
        f_execle();
        _exit(0);
    }

    waitpid(pid, NULL, 0);
    printf("\n");

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
        f_execvp();
        _exit(0);
    }

    waitpid(pid, NULL, 0);
    printf("\n");

    pid = fork();
    if(-1 == pid)
    {
        printf("fork err:%m\n");
        return -1;
    }
    else if(0 == pid)
    {
        f_execvpe();
        _exit(0);
    }

    waitpid(pid, NULL, 0);
    printf("\n");

    f_system();
    printf("\n");

    printf("parent\n");
}
