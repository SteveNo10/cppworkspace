/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-24
* Descript: 
*
============================================================================*/

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

int num = 1000;
sem_t sem;

void* f_sale(void* arg)
{
    while(true)
    {
        sem_wait(&sem);
        if(num > 0)
        {
            printf("%s sale ticket %d\n", (char*)arg, num--);
            sem_post(&sem);
        }
        else
        {
            sem_post(&sem);
            break;
        }
    }

    return arg;
}

int main(int, char**)
{
    sem_init(&sem, 0, 1);

    pthread_t pt1, pt2;
    char pname1[] = "pthread1";
    char pname2[] = "pthread2";

    pthread_create(&pt1, NULL, f_sale, pname1);
    pthread_create(&pt2, NULL, f_sale, pname2);

    pthread_join(pt1, NULL);
    pthread_join(pt2, NULL);

    sem_destroy(&sem);

    return 0;
}
