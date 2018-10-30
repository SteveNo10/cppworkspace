/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-30
* Descript: 
*
============================================================================*/

#ifndef __COMMON_SOCKET_H__
#define __COMMON_SOCKET_H__

#include <stdint.h>
#include <fcntl.h>

const uint16_t port = 8888;
const char localhost[] = "127.0.0.1";

int set_nonblock(int socket)
{
    int flags;

    if((flags = fcntl(socket, F_GETFL, 0)) < 0)
    {
        return -1;
    }

    if(fcntl(socket, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        return -1;
    }

    return 0;
}

#endif
