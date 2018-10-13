/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-13
* Descript: 
*
============================================================================*/

#include "semdemo.h"
#include <stdio.h>

int sem_comm(int nsems, int semflag, key_t key, const char* pathname)
{
    if(0 == key)
    {
        key = ftok(pathname, 0);
        if(-1 == key)
        {
            perror("ftok err");
            return -1;
        }
    }

    int semid = semget(key, nsems, semflag);
    if(-1 == semid)
    {
        perror("semget err");
    }

    return semid;
}

int sem_create(int nsems, key_t key, const char* pathname)
{
    return sem_comm(nsems, IPC_CREAT|IPC_EXCL|0666, key, pathname);
}

int sem_get(key_t key, const char* pathname)
{
    return sem_comm(0, IPC_CREAT, key, pathname);
}

int sem_destroy(int semid)
{
    int ret = semctl(semid, 0, IPC_RMID, NULL);
    if(-1 == ret)
    {
        perror("semctl err");
    }

    return ret;
}

union semun
{
    int val;
    struct semid_ds* buf;
    unsigned short* array;
    struct seminfo* __buf;
};

int sem_init(int semid, int semnum, int val)
{
    union semun seminfo;
    seminfo.val = val;

    int ret = semctl(semid, semnum, SETVAL, seminfo);
    if(-1 == ret)
    {
        perror("semctl err");
    }

    return ret;
}

int sem_op_comm(int semid, unsigned short sem_num, short sem_op)
{
    struct sembuf sem = {sem_num, sem_op, 0};
    int ret = semop(semid, &sem, 1);
    if(-1 == ret)
    {
        perror("semop err");
    }
    
    return ret;
}

int sem_p(int semid, int sem_num)
{
    return sem_op_comm(semid, sem_num, -1);
}

int sem_v(int semid, int sem_num)
{
    return sem_op_comm(semid, sem_num, 1);
}

