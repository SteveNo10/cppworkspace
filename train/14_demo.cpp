/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-16
* Descript: 
*
============================================================================*/

#include <iostream>

using namespace std;

bool IsOdd(int val)
{
    if((val & 0x1) == 1)
    {
        return true;
    }

    return false;
}

void ReOrder(int* arr, int len)
{
    if(arr == NULL || len < 2)
    {
        return;
    }

    int begin = 0;
    int end = len - 1;
    while(begin < end)
    {
        while(begin < end && IsOdd(arr[begin]))
        {
            ++begin;
        }

        while(begin < end && !IsOdd(arr[end]))
        {
            --end;
        }

        int tmp = arr[begin];
        arr[begin] = arr[end];
        arr[end] = tmp;
    }
}

void Print(int* arr, int len)
{
    if(arr == NULL || len < 1)
    {
        return;
    }

    for(int i = 0; i < len; ++i)
    {
        cout<<arr[i]<<" ";
    }

    cout<<endl;
}

int main(int, char**)
{
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ReOrder(arr, 10);
    Print(arr, 10);

    return 0;
}
