/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-26
* Descript: 
*
============================================================================*/

#include <unistd.h>

int main(int, char**)
{
    while(true)
    {
        int* p = new int(10);
        *p = 20;
        usleep(1000);
    }

    return 0;
}
