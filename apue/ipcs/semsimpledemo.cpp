/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-13
* Descript: 
*
============================================================================*/

#include "semdemo.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

void write_c(const char* str)
{
    write(STDOUT_FILENO, str, 1);
    usleep(500000);
}

int main(int, char**)
{
    int semid_p = sem_create(1);
    if(-1 == semid_p)
    {
        return -1;
    }

    if(-1 == sem_init(semid_p, 0, 1))
    {
        return -1;
    }

    pid_t pid = fork();
    if(-1 == pid)
    {
        perror("fork err");
        return -1;
    }
    else if(0 == pid)
    {
        int semid_c = sem_get();

        for(int i = 0; i < 10; ++i)
        {
            if(-1 == sem_p(semid_c, 0))
            {
                return -1;
            }

            write_c("w");
            write_c("o");
            write_c("r");
            write_c("l");
            write_c("d");
            write_c("!");
            write_c("\n");

            if(-1 == sem_v(semid_c, 0))
            {
                return -1;
            }
        }
    }
    else
    {
        for(int i = 0; i < 10; ++i)
        {
            if(-1 == sem_p(semid_p, 0))
            {
                return -1;
            }

            write_c("h");
            write_c("e");
            write_c("l");
            write_c("l");
            write_c("o");
            write_c(" ");

            if(-1 == sem_v(semid_p, 0))
            {
                return -1;
            }
        }

        waitpid(pid, NULL, 0);

        if(-1 == sem_destroy(semid_p))
        {
            perror("sem_destroy");
            return -1;
        }
    }

    return 0;
}
