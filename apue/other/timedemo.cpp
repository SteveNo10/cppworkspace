/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-17
* Descript: 
*
*    <<<字符串>>>        <<<格式化字符串>>>
*        ↑  ↑                   │↑
*        |  │asctime    strptime││strftime
*        |  │                   ↓│
*        | <<<<<<<< struct tm >>>>>>>>
*   ctime|       ↑  ↑            |
*        | gmtime│  |            |mkitme
*        |       │  |localtime   |
*        └-----┐ │  |            |
*              | │  |            ↓
* timeval---→<<<<<<<< time_t >>>>>>>>←-----timespec
*    ↑   tv_sec          ↑           tv_sec   ↑
*    │                   │                    │
*    │ gettimeofday      │    clock_gettime   │
*    └──────────────<<<内核>>>────────────────┘
*
============================================================================*/

#include <time.h>
#include <stdio.h>
#include <sys/time.h>

int main(int, char**)
{
    time_t t1;
    time(&t1);

    time_t t2 = time(NULL);
    
    timeval tmval;
    gettimeofday(&tmval, NULL);
    time_t t3 = tmval.tv_sec;

    struct tm* ptm = localtime(&t2);
    char* ptime1 = asctime(ptm);
    char* ptime2 = ctime(&t2);
    

    return 0;
}
