/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-29
* Descript: 
*
============================================================================*/

#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

const int num = 5;
sem_t sems[num];
sem_t sem_dining_num;
#define LEFT idx
#define RIGHT (idx+1)%5

void* f_run(void* arg)
{
    int idx = *(int*)arg;

    while(true)
    {
        printf("%d philosopher thinking...\n", idx);

        sem_wait(&sem_dining_num);
        sem_wait(&sems[LEFT]);
        printf("%d philosopher get %d chopsticks\n", idx, LEFT);
        sem_wait(&sems[RIGHT]);

        printf("%d philosopher eating\n", idx);

        sem_post(&sems[RIGHT]);
        sem_post(&sems[LEFT]);
        sem_post(&sem_dining_num);
    }

    return arg;
}

int main(int, char**)
{
    int idxs[num] = {0, 1, 2, 3, 4};
    for(int i = 0; i < num; ++i)
    {
        sem_init(&sems[i], 0, 1);
    }

    sem_init(&sem_dining_num, 0, 4);

    pthread_t pts[num];

    for(int i = 0; i < num; ++i)
    {
        pthread_create(&pts[i], NULL, f_run, (void*)&idxs[i]);
    }

    for(int i = 0; i < num; ++i)
    {
        pthread_join(pts[i], NULL);
    }

    sem_destroy(&sem_dining_num);

    for(int i = 0; i < num; ++i)
    {
        sem_destroy(&sems[i]);
    }

    return 0;
}
