/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-18
* Descript: 
* cout 只有一个<<时线程安全，拼接多个<<时线程不安全
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
    CLock<CMutex> lock(g_mutex_io);
    cout<<str;
}

void* f_fun1(void* tname)
{
    pthread_t tid = pthread_self();
    char buf[BUFSIZ] = {0};
    for(int i = 0; i < 3; ++i)
    {
        bzero(buf, BUFSIZ);
        snprintf(buf, BUFSIZ, "%s id:%lu say %d\n", (char*)tname, tid, i); 
        atom_print(buf);
    }

    return NULL;
}

int main(int, char**)
{
    pthread_t pt1;
    const char tname1[] = "thread1";
    pthread_create(&pt1, NULL, f_fun1, (void*)tname1);

    pthread_join(pt1, NULL);

    return 0;
}
