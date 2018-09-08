/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-08-28
* Descript: creat/open/read/write/lseek/close
============================================================================*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

int main(int, char**)
{
    const char* filename = "./test.txt";
    const char* hello = "Hello World!";
    int fd = open(filename, O_CREAT|O_RDWR, S_IRWXU|S_IRGRP|S_IROTH);
    if(-1 == fd)
    {
        printf("open err! errno:%d, errmsg:%s", errno, strerror(errno));
        return -1;
    }

    ssize_t wlen = write(fd, hello, strlen(hello));
    if(-1 == wlen)
    {
        printf("write err! errno:%d, errmsg:%s", errno, strerror(errno));
        return -1;
    } 

    off_t olen = lseek(fd, 0, SEEK_SET);
    if(-1 == olen)
    {
        printf("lseek err! errno:%d, errmsg:%s", errno, strerror(errno));
        return -1;
    }

    char buf[BUFSIZ] = {0};
    ssize_t rlen = read(fd, buf, BUFSIZ);
   if(-1 == rlen)
   {
       printf("read err! errno:%d, errmsg:%s", errno, strerror(errno));
       return -1;
   } 

   printf("read:%s\n", buf);

   close(fd);
}
