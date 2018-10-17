/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-17
* Descript: 
*
============================================================================*/

#include "flockdemo.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

const char filename[] = "./flock.txt";
const char def = 10;
char num[1] = {def};

int main(int, char**)
{
    int fd = -1;
    bool isExist = (access(filename, F_OK) != -1);
    if(isExist)
    {
        fd = open(filename, O_RDWR);
        if(-1 == fd)
        {
            perror("open err");
            return -1;
        }
    }
    else
    {
        fd = open(filename, O_RDWR|O_CREAT|O_EXCL|O_TRUNC, 0664);
        if(-1 == fd)
        {
            perror("open err");
            return -1;
        }

        writew_lock(fd, 0, SEEK_SET, 1);
        write(fd, num, 1);
        un_lock(fd, 0, SEEK_SET, 1);
    }

    pid_t pid = getpid();
    char buf[BUFSIZ] = {0};
    while(true)
    {
        writew_lock(fd, 0, SEEK_SET, 1);
        bzero(num, 1);
        lseek(fd, 0, SEEK_SET);
        read(fd, num, 1);

        bzero(buf, BUFSIZ);
        int len = snprintf(buf, BUFSIZ, "pid:%d sale ticekt:%d\n", pid, (int)num[0]);
        write(STDOUT_FILENO, buf, len);
        --num[0];
        if(0 == num[0])
        {
            num[0] = def;
        }
        lseek(fd, 0, SEEK_SET);
        write(fd, num, 1);

        un_lock(fd, 0, SEEK_SET, 1);
        usleep(10000);
    }

    return 0;
}
