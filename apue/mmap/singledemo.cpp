/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-18
* Descript: 
*
============================================================================*/

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

const char* filename = "./single.mmap";

int main(int, char**)
{
    int fd = open(filename, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
    if(-1 == fd)
    {
        printf("open err:%d msg:%m\n", errno);
        return -1;
    }

    if(-1 == ftruncate(fd, BUFSIZ))
    {
        printf("funcate err:%d msg:%m\n", errno);
        return -2;
    }

    struct stat st;
    if(-1 == fstat(fd, &st))
    {
        printf("fstat err:%d msg:%m\n", errno);
        return -3;
    }

    char* p = (char*)mmap(NULL, st.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if((void*)-1 == p)
    {
        printf("mmap err:%d msg:%m\n", errno);
        return -4;
    }

    close(fd);

    for(int i = 0; i < 26; ++i)
    {
        *p++ = i + 'a';
    }

    *p = '\n';

    munmap(p, st.st_size);

    FILE* pFile = fopen(filename, "r");
    if(NULL == pFile)
    {
        printf("fopen err:%d msg:%m\n", errno);
        return -5;
    }

    char buf[BUFSIZ] = {0};
    while(fgets(buf, BUFSIZ, pFile) != NULL)
    {
        fputs(buf, stdout);
    }

    fclose(pFile);

    return 0;
}
