/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-19
* Descript: 
*
============================================================================*/

#include "timing_msec.h"
#include "timing_nsec.h"
#include <math.h>

void calc()
{
    for(int i = 0; i < 1000000000; ++i)
    {
        sqrt(i);
    }
}

int main(int, char**)
{
    {
        CTimingMsec timing_msec;
        calc();
    }

    {
        CTimingNsec timing_nsec;
        calc();
    }

    return 0;
}
