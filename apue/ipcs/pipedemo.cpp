/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-10
* Descript: 
*
============================================================================*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int, char**)
{
    int pipefd[2] = {0};

    if(-1 == pipe(pipefd))
    {
        perror("pipe err");
        return -1;
    }

    pid_t pid = fork();
    if(-1 == pid)
    {
        perror("fork err");
        return -2;
    }
    else if(0 == pid)
    {
        sleep(1);
        close(pipefd[1]);
        char buf[BUFSIZ] = {0};
        read(pipefd[0], buf, BUFSIZ);
        char bufall[BUFSIZ] = {0};
        int n = snprintf(bufall, BUFSIZ, "read from parent:%s\n", buf);
        write(STDOUT_FILENO, bufall, n);
        close(pipefd[0]);
        return 0;
    }
    else
    {
        close(pipefd[0]);
        char say[] = "this is parent";
        write(pipefd[1], say, strlen(say));
        close(pipefd[1]);
    }

    sleep(1);

    if(-1 == pipe(pipefd))
    {
        perror("pipe err");
        return -3;
    }

    pid = fork();
    if(-1 == pid)
    {
        perror("fork err");
        return -4;
    }
    else if(0 == pid)
    {
        close(pipefd[0]);
        char say[] = "this is child";
        write(pipefd[1], say, strlen(say));
        close(pipefd[1]);
        return 0;
    }
    else
    {
        sleep(1);
        close(pipefd[1]);
        char buf[BUFSIZ] = {0};
        read(pipefd[0], buf, BUFSIZ);
        char bufall[BUFSIZ] = {0};
        int n = snprintf(bufall, BUFSIZ, "read from child:%s\n", buf);
        write(STDOUT_FILENO, bufall, n);
        close(pipefd[0]);
    }

    return 0;
}
