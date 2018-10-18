/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-18
* Descript: 
*
============================================================================*/

#ifndef __MUTEXDEMO_H__
#define __MUTEXDEMO_H__

#include <pthread.h>

class CMutex
{
public:
    CMutex();
    ~CMutex();

    void lock() const;
    bool trylock() const;
    void unlock() const;

protected:
    mutable pthread_mutex_t m_mutex;
};

#endif
