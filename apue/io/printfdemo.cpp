/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-12
* Descript: 
*
============================================================================*/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <map>

using namespace std;

void PrintCode(FILE* pFile)
{
    char buf[BUFSIZ] = {0};
    while(fgets(buf, BUFSIZ, pFile) != NULL)
    {
        if(NULL == strstr(buf, "PrintCode"))
        {
            continue;
        }

        char* substr = strstr(buf, "printf");
        if(NULL == substr)
        {
            continue;
        }
        else
        {
            char* semicolon = rindex(substr, ';');
            *semicolon = 0;
            printf("%s : ", substr);
            break;
        }
    }
}

int main(int, char**)
{
    FILE* pFile = fopen("./printfdemo.cpp", "r");
    if(NULL == pFile)
    {
        printf("fopen err:%d, msg:%s\n", errno, strerror(errno));
        return -1;
    }

    PrintCode(pFile); printf("%d %i\n", (int)12, (int)12);
    PrintCode(pFile); printf("%hhd\n", (char)'A');
    PrintCode(pFile); printf("%hd\n", (short)12);
    PrintCode(pFile); printf("%ld\n", (long)12);
    PrintCode(pFile); printf("%lld\n", (long long)12);
    PrintCode(pFile); printf("%jd\n", (intmax_t)12);
    PrintCode(pFile); printf("%zd\n", (size_t)12);
    PrintCode(pFile); printf("%td\n", (ptrdiff_t)12l);

    PrintCode(pFile); printf("%o %u %x %X\n", 123, 123, 123, 123);
    PrintCode(pFile); printf("%hho %hhu %hhx %hhX\n", 'A', 'A', 'A', 'A');
    PrintCode(pFile); printf("%ho %hu %hx %hX\n", (unsigned)123, (uint16_t)123, (uint16_t)123, (uint16_t)123);
    PrintCode(pFile); printf("%lo %lu %lx %lX\n", (unsigned long)123, (long)123, (long)123, (long)123);
    PrintCode(pFile); printf("%u\n", 12);
    PrintCode(pFile); printf("%x\n", 12);
    PrintCode(pFile); printf("%X\n", 12);
    PrintCode(pFile); printf("%o\n", 12);
    PrintCode(pFile); printf("%u\n", 12);
    PrintCode(pFile); printf("%x\n", 12);
    PrintCode(pFile); printf("%X\n", 12);

    PrintCode(pFile); printf("%e\n", 13.14159267);
    PrintCode(pFile); printf("%E\n", 13.14159267);
    PrintCode(pFile); printf("%f\n", 13.14159267);
    PrintCode(pFile); printf("%F\n", 13.14159267);
    PrintCode(pFile); printf("%g\n", 13.14159267);
    PrintCode(pFile); printf("%G\n", 13.14159267);
    PrintCode(pFile); printf("%a\n", 13.14159267);
    PrintCode(pFile); printf("%A\n", 13.14159267);

    PrintCode(pFile); printf("%c\n", 97);
    PrintCode(pFile); printf("%s\n", "Hello World!");
    PrintCode(pFile); printf("%p\n", PrintCode);

    int num = 0;
    PrintCode(pFile); printf("abcdefg%n\n", &num);
    PrintCode(pFile); printf("num:%d\n", num);

    open("aaabbbccc", 0);
    PrintCode(pFile); printf("errmsg: %m\n");

    PrintCode(pFile); printf("%%\n");

    PrintCode(pFile); printf("%#o\n", 12);
    PrintCode(pFile); printf("%#x\n", 12);
    PrintCode(pFile); printf("%#X\n", 12);
    PrintCode(pFile); printf("%d\n", 12);
    PrintCode(pFile); printf("%d\n", 12);
    PrintCode(pFile); printf("%d\n", 12);
    PrintCode(pFile); printf("%d\n", 12);
    PrintCode(pFile); printf("%d\n", 12);
    PrintCode(pFile); printf("%d\n", 12);
    PrintCode(pFile); printf("%d\n", 12);
    PrintCode(pFile); printf("%d\n", 12);
    PrintCode(pFile); printf("%d\n", 12);

    fclose(pFile);

    return 0;
}
