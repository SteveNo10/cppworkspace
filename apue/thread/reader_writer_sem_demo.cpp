/*============================================================================
 * Copyright (C) 2018 Ltd. All rights reserved.
 * Author  : SteveNo10
 * Time    : 2018-10-27
 * Descript: 
 *
 ============================================================================*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

int content = 0;
int w = 1;
int rnum = 0;
pthread_mutex_t mutex;
sem_t sem;

void* f_write(void* arg)
{
    while(true)
    {
        sem_wait(&sem);
        content = w++;
        printf("writer%d write %d\n", arg, content);
        sem_post(&sem);

        usleep(100000);
    }

    return arg;
}

void* f_read(void* arg)
{
    while(true)
    {
        pthread_mutex_lock(&mutex);
        if(0 == rnum)
        {
            sem_wait(&sem);
        }
        ++rnum;
        pthread_mutex_unlock(&mutex);

        printf("reader%d read %d\n", arg, content);

        pthread_mutex_lock(&mutex);
        --rnum;
        if(0 == rnum)
        {
            sem_post(&sem);
        }    
        pthread_mutex_unlock(&mutex);

        usleep(100000);
    }

    return arg;
}

int main(int, char**)
{
    pthread_mutex_init(&mutex, NULL);
    sem_init(&sem, 0, 1);

    const int reader_num = 10;
    const int writer_num = 10;

    pthread_t pt_readers[reader_num] = {0};
    pthread_t pt_writers[writer_num] = {0};

    for(int i = 0; i < reader_num; ++i)
    {
        pthread_create(&pt_readers[i], NULL, f_read, (void*)(i+1));
    }

    for(int i = 0; i < writer_num; ++i)
    {
        pthread_create(&pt_writers[i], NULL, f_write, (void*)(i+1));
    }

    for(int i = 0; i < reader_num; ++i)
    {
        pthread_join(pt_readers[i], NULL);
    }

    for(int i = 0; i < writer_num; ++i)
    {
        pthread_join(pt_writers[i], NULL);
    }

    sem_destroy(&sem);
    pthread_mutex_destroy(&mutex);

    return 0;
}
