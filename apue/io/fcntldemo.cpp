/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-07
* Descript: 
* 用法：
* ./main 0 < /dev/tty   "read only"
* ./main 1 > test.txt
* cat test.txt   "write only"
* ./main 2 2>>test.txt   "write only \n append mode"
* ./main 5 5<>test.txt   "read write"   表示在文件描述符5上打开文件
============================================================================*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("usage: ./main <descriptor#>\n");
        return -1;
    }

    int ret = fcntl(atoi(argv[1]), F_GETFL, 0);
    if(-1 == ret)
    {
        printf("fcntl err:%d, msg:%s\n", errno, strerror(errno));
        return -3;
    }

    switch(ret & O_ACCMODE)
    {
    case O_RDONLY:
        printf("read only\n");
        break;
    case O_WRONLY:
        printf("write only\n");
        break;
    case O_RDWR:
        printf("read write\n");
        break;
    default:
        printf("unknow access mode!\n");
        break;
    }

    if(ret & O_APPEND)
    {
        printf("append mode\n");
    }

    if(ret & O_NONBLOCK)
    {
        printf("nonblock mode\n");
    }

    if(ret & O_ASYNC)
    {
        printf("async mode\n");
    }

    if(ret & O_DIRECT)
    {
        printf("direct mode\n");
    }

    if(ret & O_NOATIME)
    {
        printf("noatime mode\n");
    }

    return 0;
}
