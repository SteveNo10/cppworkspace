/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-18
* Descript: 
*
============================================================================*/

#include "mutexdemo.h"

CMutex::CMutex()
{
    pthread_mutex_init(&m_mutex, NULL);
}

CMutex::~CMutex()
{
    pthread_mutex_destroy(&m_mutex);
}

void CMutex::lock() const
{
    pthread_mutex_lock(&m_mutex);
}

bool CMutex::trylock() const
{
    int ret = pthread_mutex_trylock(&m_mutex);
    return (0 == ret);
}

void CMutex::unlock() const
{
    pthread_mutex_unlock(&m_mutex);
}
