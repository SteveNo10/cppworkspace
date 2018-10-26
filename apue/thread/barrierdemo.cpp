/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-26
* Descript: 
*
============================================================================*/

#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;
pthread_barrier_t barrier;
int num = 1000;

void* f_sale(void* arg)
{
    while(true)
    {
        pthread_mutex_lock(&mutex);
        if(num <= 500)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
        printf("%s sale ticket:%d\n", (char*)arg, num--);

        pthread_mutex_unlock(&mutex);
    }

    int ret = pthread_barrier_wait(&barrier);
    if(0 == ret)
    {
        printf("%s exit!\n", (char*)arg);
    }
    else if(PTHREAD_BARRIER_SERIAL_THREAD)
    {
        while(true)
        {
            printf("%s continue sale ticket:%d\n", (char*)arg, num--);
            if(num <= 0)
            {
                break;
            }
        }
    }
    else
    {
        perror("pthread_barrier_wait err!");
    }

    return arg;
}

int main(int, char**)
{
    pthread_mutex_init(&mutex, NULL);
    pthread_barrier_init(&barrier, NULL, 3);

    pthread_t pt1, pt2, pt3;
    char pname1[] = "pthread1";
    char pname2[] = "pthread2";
    char pname3[] = "pthread3";

    pthread_create(&pt1, NULL, f_sale, pname1);
    pthread_create(&pt2, NULL, f_sale, pname2);
    pthread_create(&pt3, NULL, f_sale, pname3);

    pthread_join(pt1, NULL);
    pthread_join(pt2, NULL);
    pthread_join(pt3, NULL);

    pthread_barrier_destroy(&barrier);
    pthread_mutex_destroy(&mutex);

    return 0;
}
