/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-16
* Descript: 
*
============================================================================*/

#include <iostream>

using namespace std;

void Print(int* arr, int len)
{
    int idx = -1;
    for(int i = 0; i < len; ++i)
    {
        if(arr[i] != '0')
        {
            idx = i;
            break;
        }
    }

    if(idx == -1)
    {
        cout<<'0';
    }
    else
    {
        for(int i = idx; i < len; ++i)
        {
            cout<<(char)(arr[i]);
        }
    }

    cout<<endl;
}

void PrintRecursion(int* arr, int len, int idx)
{
    if(idx == len)
    {
        Print(arr, len);
        return;
    }

    for(int i = 0; i < 10; ++i)
    {
        arr[idx] = i + '0';
        PrintRecursion(arr, len, idx + 1);
    }
}

int main(int, char**)
{
    int n = 0;
    while(true)
    {
        cin>>n;
        if(n <= 0)
        {
            break;
        }

        int* arr = new int[n+1];
        arr[n] = 0;
        PrintRecursion(arr, n, 0);
    }
}
