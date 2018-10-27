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

const int BUFSIZE = 10;
int products[BUFSIZE] = {0};
sem_t sem_full;
sem_t sem_empty;
pthread_mutex_t mutex;
int pro_idx = 0;
int con_idx = 0;
int product = 100;

void* f_product(void* arg)
{
    while(true)
    {
        sem_wait(&sem_full);
        pthread_mutex_lock(&mutex);

        if(product <= 200)
        {
            products[pro_idx] = product++;
            printf("prd%d at idx %d product %d\n", arg, pro_idx, products[pro_idx]);
            pro_idx = (pro_idx+1) % BUFSIZE;
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            break;
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&sem_empty);
    }

    return arg;
}

void* f_consume(void* arg)
{
    while(true)
    {
        sem_wait(&sem_empty);
        pthread_mutex_lock(&mutex);

        printf("con%d consume idx %d %d\n", arg, con_idx, products[con_idx]);
        con_idx = (con_idx+1) % BUFSIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&sem_full);
    }

    return arg;
}

int main(int, char**)
{
    sem_init(&sem_full, 0, BUFSIZE);
    sem_init(&sem_empty, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    const int thread_pro_num = 10;
    const int thread_con_num = 10;
    pthread_t pt_pros[thread_pro_num] = {0};
    pthread_t pt_cons[thread_con_num] = {0};

    for(int i = 0; i < thread_pro_num; ++i)
    {
        pthread_create(&pt_pros[i], NULL, f_product, (void*)(i+1));
    }

    for(int i = 0; i < thread_con_num; ++i)
    {
        pthread_create(&pt_cons[i], NULL, f_consume, (void*)(i+1));
    }

    for(int i = 0; i < thread_pro_num; ++i)
    {
        pthread_join(pt_pros[i], NULL);
    }

    for(int i = 0; i < thread_con_num; ++i)
    {
        pthread_join(pt_cons[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem_empty);
    sem_destroy(&sem_full);

    return 0;
}
