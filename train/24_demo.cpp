/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-26
* Descript: 
*
============================================================================*/

#include <iostream>

using namespace std;

bool IsBackList(int* arr, int begin, int end)
{
    if(NULL == arr || begin > end)
    {
        return false;
    }

    int root = arr[end];
    int more_idx = begin;
    for(;more_idx <= end - 1; ++more_idx)
    {
        if(arr[more_idx] > root)
        {
            break;
        } 
    }

    for(int j = more_idx; j <= end - 1; ++j)
    {
        if(arr[j] < root)
        {
            return false;
        }
    }

    bool bIsBackList = true;
    if(more_idx > begin)
    {
        bIsBackList = IsBackList(arr, begin, more_idx - 1);
        if(!bIsBackList)
        {
            return bIsBackList;
        }
    }

    if(more_idx < end - 1)
    {
        bIsBackList = IsBackList(arr, more_idx, end - 1);
    }

    return bIsBackList;
}

int main(int, char**)
{
    // int arr[7] = {5, 7, 6, 9, 11, 10, 8};
    int arr[7] = {5, 12, 6, 9, 11, 10, 8};
    if(IsBackList(arr, 0, 6))
    {
        cout<<"Yes"<<endl;
    }
    else
    {
        cout<<"No"<<endl;
    }

    return 0;
}
