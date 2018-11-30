/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-11-12
* Descript: 
*
============================================================================*/

#ifndef __SINGLETON_LAZY_H__
#define __SINGLETON_LAZY_H__

#include <pthread.h>

class CSingletonLazy
{
public:
    static CSingletonLazy* get_instance();

    void print();

private:
    CSingletonLazy();
    CSginletonLazy(const CSingletonLazy& singleton);
    CSingletonLazy& operator=(const CSingletonLazy& singleton);

private:
    static CSingletonLazy* m_instance;
    static pthread_mutex_t m_mutex;

};

#endif
