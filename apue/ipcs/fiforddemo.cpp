/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-11
* Descript: 
*
============================================================================*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int, char**)
{
    const char filename[] = "./fifo.fifo";
    if(-1 == access(filename, F_OK))
    {
        if(-1 == mkfifo(filename, 0664))
        {
            perror("mkfifo err");
            return -1;
        }
    }

    int fd = open(filename, O_RDONLY);
    if(-1 == fd)
    {
        perror("open err");
        return -2;
    }

    char buf[BUFSIZ] = {0};
    read(fd, buf, BUFSIZ);
    printf("read from fifo: %s\n", buf);

    close(fd);

    return 0;
}
