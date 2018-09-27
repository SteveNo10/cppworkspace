/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-27
* Descript: 
*
============================================================================*/

#include <stdio.h>

extern char** environ;

int main(int argc, char* argv[])
{
    for(int i = 0; i < argc; ++i)
    {
        printf("arg %d : %s\n", i, argv[i]);
    }

    for(int i = 0; environ[i] != NULL; ++i)
    {
        printf("%s\n", environ[i]);
    }

    return 0;
}
