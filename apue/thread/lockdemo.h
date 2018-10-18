/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-18
* Descript: 
*
============================================================================*/

#ifndef __LOCKDEMO_H__
#define __LOCKDEMO_H__

template<typename T>
class CLock
{
public:
    CLock(const T& mutex):
        m_mutex(mutex)
    {
        m_mutex.lock();
    }

    ~CLock()
    {
        m_mutex.unlock();
    }

private:
    CLock(const CLock&);
    CLock& operator=(const CLock&);

private:
    const T& m_mutex;
};

#endif
