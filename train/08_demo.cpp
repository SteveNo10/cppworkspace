/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-15
* Descript: 
*
============================================================================*/

#include <iostream>

using namespace std;

int Head(int* arr, int len)
{
    if(arr == NULL || len < 1)
    {
        return -1;
    }

    int head = 0;
    int tail = len - 1;
    int mid = head;
    while(arr[head] >= arr[tail])
    {
        if(head + 1 == tail)
        {
            mid = tail;
            break;
        }

        mid = (head + tail) / 2;
        if(arr[mid] == arr[head] && arr[mid] == arr[tail])
        {
            int minnum = arr[head];
            for(int i = head + 1; i <= tail; ++i)
            {
                if(arr[i] < minnum)
                {
                    return i;
                }
            }
        }

        if(arr[head] <= arr[mid])
        {
            head = mid;
        }
        else if(arr[tail] >= arr[mid])
        {
            tail = mid;
        }
    }

    return mid;
}

int main(int, char**)
{
    // int arr[10] = {4, 5, 6, 7, 8, 9, 10, 1, 2, 3};
    int arr[10] = {1, 0, 1, 1, 1, 1, 1, 1, 1, 1};
    // int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int head_idx = Head(arr, 10);
    cout<<"head_idx:"<<head_idx<<", head:"<<arr[head_idx]<<endl;
}
