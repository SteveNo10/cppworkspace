/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-08
* Descript: 
* struct dirent->d_type 不能判断类型，需要用struct stat->st_mode判断是否目录
============================================================================*/

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void RecPrint(const char* path)
{
    static int deep = 0;
    ++deep;
    DIR* dir = opendir(path);
    if(NULL == dir)
    {
        printf("opendir err:%d, msg:%s\n", errno, strerror(errno));
        exit(-2);
    }

    struct dirent* pDirent;
    while((pDirent = readdir(dir)) != NULL)
    {
        printf("deep:%d --- ino:%lu, off:%lu, reclen:%u, type:%d, name:%s\n", deep, pDirent->d_ino, pDirent->d_off, pDirent->d_reclen, pDirent->d_type, pDirent->d_name);

        if(strncmp(".", pDirent->d_name, sizeof(".")) == 0 ||
           strncmp("..", pDirent->d_name, sizeof("..")) == 0)
        {
            continue;
        }

        char fullpath[BUFSIZ] = {0};
        strncpy(fullpath, path, strlen(path));
        strncat(fullpath, "/", strlen("/"));
        strncat(fullpath, pDirent->d_name, strlen(pDirent->d_name));  

        struct stat oStat;
        if(-1 == stat(fullpath, &oStat))
        {
            printf("path:%s stat err:%d, msg:%s\n", fullpath, errno, strerror(errno));
            exit(3);
        }

        if(S_ISDIR(oStat.st_mode))
        {
            RecPrint(fullpath);
        }
    }

    closedir(dir);
    --deep;
}

int main(int argc, char* argv[])
{
    if(2 != argc)
    {
        printf("Usage: ./main directpath\n");
        return -1;
    }

    char buf[BUFSIZ] = {0};
    realpath(argv[1], buf);

    printf("path:%s\n", buf);

    RecPrint(buf);
    return 0;
}
