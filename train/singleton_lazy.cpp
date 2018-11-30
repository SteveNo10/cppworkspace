/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-11-12
* Descript: 
*
============================================================================*/

#include "singleton_lazy.h"

CSingletonLazy* CSingletonLazy::m_instance = NULL;
pthread_mutex_t CSingletonLazy::m_mutex = PTHREAD_MUTEX_INITIALIZER;

CSingletonLazy::CSingletonLazy()
{

}

CSingletonLazy::CSingletonLazy(const CSingletonLazy& /*singleton*/)
{

}

CSingletonLazy& CSingletonLazy::operator=(const CSingletonLazy& /*singleton*/)
{

}

void CSingletonLazy::print()
{
    printf("this is singleton lazy\n");
}

CSingletonLazy* get_instance()
{
    if(NULL == m_instance)
    {
        pthread_mutex_lock(&m_mutex);
        if(NULL == m_instance)
        {
            m_instance = new CSingletonLazy();
        }
        pthread_mutex_unlock(&m_mutex);
    }

    return m_instance;
}
