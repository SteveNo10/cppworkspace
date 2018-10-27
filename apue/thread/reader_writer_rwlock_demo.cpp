/*============================================================================
 * Copyright (C) 2018 Ltd. All rights reserved.
 * Author  : SteveNo10
 * Time    : 2018-10-27
 * Descript: 
 *
 ============================================================================*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int content = 0;
int w = 1;
pthread_rwlock_t rwlock;

void* f_read(void* arg)
{
    while(true)
    {
        pthread_rwlock_rdlock(&rwlock);

        printf("reader%d read %d\n", arg, content);

        pthread_rwlock_unlock(&rwlock);

        usleep(100000);
    }

    return arg;
}

void* f_write(void* arg)
{
    while(true)
    {
        pthread_rwlock_wrlock(&rwlock);

        content = w++;
        printf("writer:%d write %d\n", arg, content);

        pthread_rwlock_unlock(&rwlock);

        usleep(100000);
    }

    return arg;
}

int main(int, char**)
{
    pthread_rwlock_init(&rwlock, NULL);

    const int reader_num = 10;
    const int writer_num = 10;
    pthread_t pt_readers[reader_num] = {0};
    pthread_t pt_writers[writer_num] = {0};

    for(int i = 0; i < reader_num; ++i)
    {
        pthread_create(&pt_readers[i], NULL, f_read, (void*)i);
    }

    for(int i = 0; i < writer_num; ++i)
    {
        pthread_create(&pt_writers[i], NULL, f_write, (void*)i);
    }

    for(int i = 0; i < reader_num; ++i)
    {
        pthread_join(pt_readers[i], NULL);
    }

    for(int i = 0; i < writer_num; ++i)
    {
        pthread_join(pt_writers[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);

    return 0;
}
