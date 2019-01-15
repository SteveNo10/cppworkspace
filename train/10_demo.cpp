/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-15
* Descript: 
*
============================================================================*/

#include <iostream>

using namespace std;

int NumOf1(int n)
{
    int count = 0;
    while(n > 0)
    {
        n = n & (n - 1);
        ++count;
    }

    return count;
}

int main(int, char**)
{
    int num = 0;
    while(true)
    {
        cin>>num;

        if(num == -1)
        {
            break;
        }

        cout<<NumOf1(num)<<endl;
    }

    return 0;
}
