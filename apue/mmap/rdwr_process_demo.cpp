/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-20
* Descript: 
*
============================================================================*/

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

const char* filename = "./rdwr_process.mmap";

void Usage()
{
    printf("Usage: ./a.out type\n  0:write\n  1:read\n");
    exit(-1);
}

void Truncate(int fd, off_t len)
{
    if(-1 == ftruncate(fd, len))
    {
        printf("ftruncate err:%m\n");
        exit(-1);
    }
}

void Write()
{
    int fd = open(filename, O_RDWR|O_CREAT, 0664);
    if(-1 == fd)
    {
        printf("open file %s err:%m\n", filename);
        exit(-1);
    }

    ftruncate(fd, 0);
    ftruncate(fd, BUFSIZ);

    char* p = (char*)mmap(NULL, BUFSIZ, PROT_WRITE, MAP_SHARED, fd, 0);
    if((void*)-1 == p)
    {
        printf("mmap err:%m\n");
        exit(-1);
    }

    close(fd);

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

    munmap(p, BUFSIZ);
}

void Read()
{
    int fd = open(filename, O_RDONLY);
    if(-1 == fd)
    {
        printf("open file %s err:%m\n", filename);
        exit(-1);
    }

    char* p = (char*)mmap(NULL, BUFSIZ, PROT_READ, MAP_PRIVATE, fd, 0);
    if((void*)-1 == p)
    {
        printf("mmap err:%m\n");
        exit(-1);
    }

    close(fd);

    while(true)
    {
        printf("%s\n", p);
        sleep(2);
    }

    munmap(p, BUFSIZ);
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        Usage();
    }

    int type = atoi(argv[1]);
    if(type != 0 && type != 1)
    {
        Usage();
    }

    if(0 == type)
    {
        Write();
    }
    else if(1 == type)
    {
        Read();
    }
    
    return 0;
}
