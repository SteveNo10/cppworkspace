/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-19
* Descript: 
*
============================================================================*/

#ifndef __TIMING_MSEC_H__
#define __TIMING_MSEC_H__

#include <sys/time.h>
#include <time.h>
#include <stdio.h>

class CTimingMsec
{
public:
    CTimingMsec()
    {
        Begin();
    }

    ~CTimingMsec()
    {
        printf("cost:%.6fs\n", End());
    }

    void Begin()
    {
        gettimeofday(&m_begin, NULL);
    }

    double End()
    {
        gettimeofday(&m_end, NULL);
        return (double)m_end.tv_sec + (double)m_end.tv_usec/1000000.0 - (double)m_begin.tv_sec - (double)m_begin.tv_usec/1000000.0;
    }

private:
    timeval m_begin;
    timeval m_end;
};

#endif
