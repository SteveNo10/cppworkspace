/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-10-18
* Descript: 
*
============================================================================*/

#include "mutexdemo.h"
#include "lockdemo.h"
#include <iostream>

using namespace std;

CMutex g_mutex_io;

void atom_print(const char* str)
{
    CLock<CMutex> lock(g_mutex_io);
    cout<<str<<endl;
}

int main(int, char**)
{

    return 0;
}
