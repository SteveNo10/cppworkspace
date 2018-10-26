/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-26
* Descript: 
*
============================================================================*/

#include <pthread.h>
#include <stdio.h>

int num = 100;
pthread_mutex_t mutex_cond;
pthread_cond_t cond;

void* f_sale_front(void* arg)
{
    while(true)
    {
        printf("thread front sale ticket:%d\n", num--);
        if(num <= 50)
        {
            pthread_cond_signal(&cond);
            break;
        }
    }

    return arg;
}

void* f_sale_back(void* arg)
{
    pthread_cond_wait(&cond, &mutex_cond);

    while(true)
    {
        printf("thread back sale ticket:%d\n", num--);
        if(num <= 0)
        {
            break;
        }    
    }

    return arg;
}

int main(int, char**)
{
    pthread_mutex_init(&mutex_cond, NULL);
    pthread_cond_init(&cond, NULL);
    
    pthread_t pt1, pt2;
    pthread_create(&pt1, NULL, f_sale_front, NULL);
    pthread_create(&pt2, NULL, f_sale_back, NULL);

    pthread_join(pt1, NULL);
    pthread_join(pt2, NULL);

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex_cond);

    return 0;
}
