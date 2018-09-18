/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-17
* Descript: 
*
*    <<<字符串>>>        <<<格式化字符串>>>
*        ↑  ↑                   │↑
*        |  │asctime    strptime││strftime
*        |  │asctime_r          ↓│
*        | <<<<<<<< struct tm >>>>>>>>
*   ctime|        ↑  ↑            |
* ctime_r|  gmtime│  |localtime   |mkitme
*        |gmtime_r│  |localtime_r |
*        └-----┐  │  |            |
*              |  │  |            ↓
* timeval---→<<<<<<<< time_t >>>>>>>>←-----timespec
*    ↑   tv_sec          ↑           tv_sec   ↑
*    │                   │                    │
*    │ gettimeofday      │    clock_gettime   │
*    └──────────────<<<内核>>>────────────────┘
*
* 后缀不带_r的函数因为共用系统变量，可能造成结果被覆盖，尽量不用
*
============================================================================*/

#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

char buf[BUFSIZ] = {0};

void print_time_t(const char* head, const time_t* t)
{
    bzero(buf, BUFSIZ);
    ctime_r(t, buf);
    printf("%s:%s", head, buf);
}

void print_tm(const char* head, const tm* ptm)
{
    bzero(buf, BUFSIZ);
    asctime_r(ptm, buf);
    printf("%s:%s", head, buf);
}

int main(int, char**)
{
    time_t t1;
    time(&t1);
    print_time_t("time()", &t1);

    time_t t2 = time(NULL);
    print_time_t("time(NULL)", &t2);
    
    timeval tmval;
    gettimeofday(&tmval, NULL);
    time_t t3 = tmval.tv_sec;
    print_time_t("gettimeofday", &t3);

    timespec tmspec;
    clock_gettime(CLOCK_MONOTONIC, &tmspec);
    time_t t4 = tmspec.tv_sec;
    print_time_t("clock_gettime", &t4);

    tm tm1;
    localtime_r(&t1, &tm1);
    print_tm("localtime_r", &tm1);

    tm tm2;
    gmtime_r(&t2, &tm2);
    print_tm("gmtime_r", &tm2);

    time_t t5 = mktime(&tm1);
    print_time_t("mktime", &t5);

    const char* format = "%Y-%m-%d %H:%M:%S";
    strftime(buf, BUFSIZ, format, &tm1);
    printf("strftime:%s\n", buf);    

    tm tm3;
    strptime("2018-08-08 08:08:08", format, &tm3);
    print_tm("strptime", &tm3);

    const char* f_all = "%Y %B %A %p %I %M %S";
    bzero(buf, BUFSIZ);
    strftime(buf, BUFSIZ, f_all, &tm1);
    printf("%s\n", buf);

    return 0;
}
