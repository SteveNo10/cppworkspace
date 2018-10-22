/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-18
* Descript: 
* cout 只有一个<<时线程安全，拼接多个<<时线程不安全
* pthread_cleanup_push/pthread_cleanup_pop 清理函数被执行三个条件：
*   1.调用pthread_exit
*   2.别的线程调用pthread_cancel
*   3.pthread_cleanup_pop参数非0
============================================================================*/

#include "mutexdemo.h"
#include "lockdemo.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

using namespace std;

CMutex g_mutex_io;

void atom_print(const char* str)
{
    // CLock<CMutex> lock(g_mutex_io);
    cout<<str;
}

void cleanup_func(void* arg)
{
    atom_print((char*)arg);
}

void f_say_hello(const char* p)
{
    pthread_t tid = pthread_self();
    char buf[BUFSIZ] = {0};
    for(int i = 0; i < 3; ++i)
    {
        bzero(buf, BUFSIZ);
        snprintf(buf, BUFSIZ, "%s id:%lu say %d\n", p, tid, i); 
        atom_print(buf);
    }
}

void f_say_end(const char* p)
{
    char buf[BUFSIZ] = {0};
    snprintf(buf, BUFSIZ, "get ret msg:%s\n", p);
    atom_print(buf);
}

void f_say_main()
{
    char buf[BUFSIZ] = {0};
    snprintf(buf, BUFSIZ, "main thread:%lu\n", pthread_self());
    atom_print(buf);
}

void f_say_create(const pthread_t& tid, const char* tname)
{
    char buf[BUFSIZ] = {0};
    snprintf(buf, BUFSIZ, "main create thread:%s tid:%lu\n", tname, tid);
    atom_print(buf);
}

void* f_fun1(void* arg)
{
    char cleanup1[BUFSIZ] = "cleanup1 ";
    strncat(cleanup1, (char*)arg, BUFSIZ);
    strncat(cleanup1, "\n", BUFSIZ);
    char cleanup2[BUFSIZ] = "cleanup2 ";
    strncat(cleanup2, (char*)arg, BUFSIZ);
    strncat(cleanup2, "\n", BUFSIZ);
    pthread_cleanup_push(cleanup_func, cleanup1);
    pthread_cleanup_push(cleanup_func, cleanup2);

    f_say_hello((char*)arg);

    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);

    return arg;
}

void* f_fun2(void* arg)
{
    char cleanup1[BUFSIZ] = "cleanup1 ";
    strncat(cleanup1, (char*)arg, BUFSIZ);
    strncat(cleanup1, "\n", BUFSIZ);
    pthread_cleanup_push(cleanup_func, cleanup1);

    f_say_hello((char*)arg);

    pthread_exit(arg);

    pthread_cleanup_pop(0);
}

void* f_fun3(void* arg)
{
    f_say_hello((char*)arg);
    return NULL;
}

void* f_fun4(void* arg)
{
    char cleanup1[BUFSIZ] = "cleanup1 ";
    strncat(cleanup1, (char*)arg, BUFSIZ);
    strncat(cleanup1, "\n", BUFSIZ);
    char cleanup2[BUFSIZ] = "cleanup2 ";
    strncat(cleanup2, (char*)arg, BUFSIZ);
    strncat(cleanup2, "\n", BUFSIZ);
    pthread_cleanup_push(cleanup_func, cleanup1);
    pthread_cleanup_push(cleanup_func, cleanup2);

    f_say_hello((char*)arg);

    while(true)
    {
        sleep(1);
    }

    return NULL;

    pthread_cleanup_pop(0);   //0表示此处不调用
    pthread_cleanup_pop(0);
}

int main(int, char**)
{
    pthread_t pt1, pt2, pt3, pt4;
    const char tname1[] = "thread1";
    const char tname2[] = "thread2";
    const char tname3[] = "thread3";
    const char tname4[] = "thread4";

    pthread_create(&pt1, NULL, f_fun1, (void*)tname1);
    f_say_create(pt1, tname1);

    pthread_create(&pt2, NULL, f_fun2, (void*)tname2);
    f_say_create(pt2, tname2);

    void* retval1 = NULL;
    pthread_join(pt1, &retval1);
    f_say_end((char*)retval1);

    void* retval2 = NULL;
    pthread_join(pt2, &retval2);
    f_say_end((char*)retval2);

    pthread_create(&pt3, NULL, f_fun3, (void*)tname3);
    f_say_create(pt3, tname3);
    pthread_detach(pt3);

    pthread_create(&pt4, NULL, f_fun4, (void*)tname4);
    f_say_create(pt4, tname4);
    // pthread_detach(pt4);

    sleep(1);

    pthread_cancel(pt4);

    sleep(1);

    return 0;
}
