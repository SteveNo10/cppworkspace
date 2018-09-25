/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-25
* Descript: 
*
============================================================================*/

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int, char**)
{
    int a = 0;

    pid_t pid = fork();
    if(-1 == pid)
    {
        printf("fork err:%m\n");
        return -1; 
    }
    else if(0 == pid)
    {
        ++a;
        printf("children a:%d\n", a);
    }
    else
    {
        printf("parent a:%d\n", a);
        waitpid(pid, NULL, 0);
    }

    return 0;
}
