/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-11-17
* Descript: 
*
============================================================================*/

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage:%s maxnum\n", argv[0]);
        return 0;
    }

    long int maxnum = atol(argv[1]);

    vector<long int> nums(maxnum);
    for(long int i = 0; i < maxnum; ++i)
    {
        nums[i] = i + 1;
    }

    srandom(time(NULL));

    for(long int i = maxnum - 1; i > 0; --i)
    {
        long int r = random() % (i + 1);
        printf("%ld ", nums[r]);
        if(i != r)
        {
            long int tmp = nums[i];
            nums[i] = nums[r];
            nums[r] = tmp;
        }        
    }

    printf("\n");
}
