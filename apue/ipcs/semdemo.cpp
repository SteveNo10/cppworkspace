/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-12
* Descript: 
*
============================================================================*/

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

const key_t KEY_VALUE = 2;

union semun
{
    int val;    // Value for SETVAL
    struct semid_ds *buf;    // Buffer for IPC_STAT, IPC_SET
    unsigned short *array;  // Array for GETALL, SETALL
    struct seminfo *__buf;  // Buffer for IPC_INFO(Linux-specific)
};

void CheckRetVal(int retval, const string & strErr)
{
    if(-1 == retval)
    {
        cout<<strErr<<endl;
        exit(-1);
    }
}

int sem_setval(int semid, int val)
{
    union semun seminfo;
    seminfo.val = val;
    return semctl(semid, 0, SETVAL, seminfo);
}

int sem_p(int semid)
{
    struct sembuf sembufinfo;
    sembufinfo.sem_num = 0;
    sembufinfo.sem_op = -1;
    sembufinfo.sem_flg = SEM_UNDO;

    return semop(semid, &sembufinfo, 1);
}

int sem_v(int semid)
{
    struct sembuf sembufinfo = {0, 1, SEM_UNDO};
    return semop(semid, &sembufinfo, 1);
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout<<"Usage:"<<argv[0]<<" msg! You must say something!"<<endl;
        return -1;
    }

    string strMsg = argv[1];

    bool bWrite = (strMsg == "start");

    int semid = semget(KEY_VALUE, 1, IPC_CREAT|0666);
    CheckRetVal(semid, "semget err");

    if(bWrite)
    {
        int ret = sem_setval(semid, 1);
        CheckRetVal(ret, "sem setval err!");
    }

    struct semid_ds seminfo;
    int ret = semctl(semid, 0, IPC_STAT, &seminfo);
    CheckRetVal(ret, "semctl err");

    cout<<"sem info: uid:"<<seminfo.sem_perm.uid<<"   num:"<<seminfo.sem_nsems<<endl;

    if(bWrite)
    {
        while(true)
        {
            ret = sem_p(semid);
            CheckRetVal(ret, "sem_p err!");

            cout<<strMsg<<endl;

            ret = sem_v(semid);
            CheckRetVal(ret, "sem_v err!");
        }
    }
    else
    {
        while(true)
        {
            ret = sem_p(semid);
            CheckRetVal(ret, "sem_p err!");

            sleep(1);
            cout<<"wait 1s"<<endl;

            ret = sem_v(semid);
            CheckRetVal(ret, "sem_v err!");
        }
    }

    return 0;
}
