/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-25
* Descript: 
* 信号量只能保证*p内容互斥，不能保证父子进程输出顺序
============================================================================*/

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

void f_sale(int fd, int* p, sem_t* sem, const char* pname)
{
    while(true)
    {
        sem_wait(sem);

        if(*p > 0)
        {
            printf("%s sale ticket %d\n", pname, (*p)--);
            sem_post(sem);
        }
        else
        {
            sem_post(sem);
            break;
        }
    }
}

int main(int, char**)
{
    sem_t sem;
    sem_init(&sem, 1, 1);

    int fd = open("./sem.txt", O_CREAT|O_RDWR|O_TRUNC, 0664);
    ftruncate(fd, BUFSIZ);
    int* p = (int*)mmap(NULL, BUFSIZ, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    *p = 1000;
    close(fd);

    pid_t pid = fork();
    if(-1 == pid)
    {
        perror("fork err!");
        return -1;
    }
    else if(0 == pid)
    {
        f_sale(fd, p, &sem, "children");
    }
    else
    {
        f_sale(fd, p, &sem, "parent");

        waitpid(pid, NULL, 0);

        munmap(p, 1);
        sem_destroy(&sem);
    }

    return 0;
}
