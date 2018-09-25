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
    pid_t pid = fork();
    if(-1 == pid)
    {
        printf("fork err:%m\n");
        return -1;
    }
    else if(0 == pid)
    {
        printf("child\n");
    }
    else
    {
        sleep(3);
        printf("parent\n");
        sleep(60 * 60);
    }

    return 0;
}
