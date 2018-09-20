/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-20
* Descript: 
*
============================================================================*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/wait.h>

const char* filename = "./rdwr_thread.mmap";

int main(int, char**)
{
    int fd = open(filename, O_CREAT|O_RDWR, 0664);
    if(-1 == fd)
    {
        printf("open file %s err:%m\n", filename);
        return -1;
    }

    struct stat st;
    if(-1 == fstat(fd, &st))
    {
        printf("fstat err:%m\n");
        return -2;
    }

    if(st.st_size < BUFSIZ)
    {
        if(-1 == ftruncate(fd, BUFSIZ))
        {
            printf("ftruncate err:%m\n");
            return -3;
        }
    }

    char* p = (char*)mmap(NULL, BUFSIZ, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    if((void*)-1 == p)
    {
        printf("mmap err:%m\n");
        return -4;
    }

    pid_t pid = fork();
    if(-1 == pid)
    {
        printf("fork err:%m\n");
        return -4;
    }
    if(0 == pid)
    {
        while(true)
        {
            printf("%s\n", p);
            sleep(2);
        }
    }
    else
    {
        int idx = 0;
        char c = 'a';
        while(true)
        {
            p[idx++] = c++;
            if(BUFSIZ < idx)
            {
                idx = 0;
            }
            if('z' < c)
            {
                c = 'a';
            }

            sleep(1);
        }

        waitpid(pid, NULL, 0);

        munmap(p, BUFSIZ);
    }

    return 0;
}
