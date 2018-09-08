/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-08
* Descript: 
*
============================================================================*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./main filepath\n");
        return -1;
    }

    struct stat st;
    int ret = stat(argv[1], &st);
    if(-1 == ret)
    {
        printf("stat err:%d, msg:%s\n", errno, strerror(errno));
        return -2;
    }

    switch(st.st_mode & S_IFMT)
    {
    case S_IFREG:
        printf("regular file\n");
        break;
    case S_IFBLK:
        printf("block device\n");
        break;
    case S_IFCHR:
        printf("character device\n");
        break;
    case S_IFDIR:
        printf("directory\n");
        break;
    case S_IFIFO:
        printf("FIFO/pipe\n");
        break;
    case S_IFLNK:
        printf("symlink\n");
        break;
    case S_IFSOCK:
        printf("socket\n");
        break;
    default:
        printf("unknow file type\n");
        break;
    }

    printf("I-node number:%ld\n", (long)st.st_ino);
    printf("Mode:%lo(octal)\n", (unsigned long)st.st_mode);
    printf("Link count:%ld\n", (long)st.st_nlink);
    printf("UID:%ld\n", (long)st.st_uid);
    printf("GID:%ld\n", (long)st.st_gid);
    printf("block size:%lld\n", (long long)st.st_size);
    printf("blocks:%lld\n", (long long)st.st_blocks);
    printf("ctime:%s", ctime(&st.st_ctime));
    printf("atime:%s", ctime(&st.st_atime));
    printf("mtime:%s", ctime(&st.st_mtime));

    return 0;
}
