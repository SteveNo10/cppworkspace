/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-19
* Descript: 
*
============================================================================*/

#ifndef __TIMING_NSEC_H__
#define __TIMING_NSEC_H__

#include <time.h>
#include <stdio.h>

class CTimingNsec
{
public:
    CTimingNsec()
    {
        Begin();
    }

    ~CTimingNsec()
    {
        printf("cost:%.9fs\n", End());
    }

    void Begin()
    {
        clock_gettime(CLOCK_MONOTONIC, &m_begin);
    }

    double End()
    {
        clock_gettime(CLOCK_MONOTONIC, &m_end);
        return (double)m_end.tv_sec + (double)m_end.tv_nsec / 1000000000.0 - (double)m_begin.tv_sec - (double)m_begin.tv_nsec / 1000000000.0;
    }

private:
    timespec m_begin;
    timespec m_end;
};

#endif
