/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-16
* Descript: 
*
============================================================================*/

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int, char**)
{
    key_t key = ftok(".", 0);
    if(-1 == key)
    {
        perror("ftok err!");
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
        int shmid = shmget(key, getpagesize(), IPC_CREAT|IPC_EXCL|0666);
        if(-1 == shmid)
        {
            perror("shmget err");
            return -1;
        }

        char* p = (char*)shmat(shmid, NULL, 0);
        if((void*)-1 == p)
        {
            perror("shmat err");
            return -1;
        }

        const char say[] = "Hello World!";
        strncpy(p, say, strlen(say));

        if(-1 == shmdt(p))
        {
            perror("shmdt err");
            return -1;
        }

        return 0;
    }

    waitpid(pid, NULL, 0);

    int shmid = shmget(key, getpagesize(), 0);
    if(-1 == shmid)
    {
        perror("shmget err");
        return -1;
    }

    char* p = (char*)shmat(shmid, NULL, 0);
    if((void*)-1 == p)
    {
        perror("shmat err");
        return -1;
    }

    printf("read:%s\n", p);

    if(-1 == shmdt(p))
    {
        perror("shmdt err");
        return -1;
    }

    if(-1 == shmctl(shmid, IPC_RMID, 0))
    {
        perror("shmctl err");
        return -1;
    }

    return 0;
}
