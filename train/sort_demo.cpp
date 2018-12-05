/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-12-05
* Descript: 
*
============================================================================*/

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void swap_val(int* arr, int idx1, int idx2)
{
    int tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;
}

int selection_sort(int* arr, int len)
{
    if(NULL == arr)
    {
        return -1;
    }

    if(len < 2)
    {
        return 0;
    }

    for(int i = 0; i < len - 1; ++i)
    {
        int min_idx = i;
        for(int j = i + 1; j < len; ++j)
        {
            if(arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }

        if(i != min_idx)
        {
            swap_val(arr, i, min_idx);
        }
    }

    return 0;
}

int bubble_sort(int* arr, int len)
{
    if(NULL == arr)
    {
        return -1;
    }

    if(len < 2)
    {
        return 0;
    }

    for(int i = len - 1; i > 0; --i)
    {
        for(int j = 0; j < i; ++j)
        {
            if(arr[j] > arr[j + 1])
            {
                swap_val(arr, j, j + 1);
            }
        }
    }

    return 0;
}

int insertion_sort(int* arr, int len)
{
    if(NULL == arr)
    {
        return -1;
    }

    if(len < 2)
    {
        return 0;
    }

    for(int i = 1; i < len; ++i)
    {
        for(int j = i; j > 1; --j)
        {
            if(arr[j] < arr[j - 1])
            {
                swap_val(arr, j, j - 1);
            }
            else
            {
                break;
            }
        }
    }

    return 0;
}

int shell_sort(int* arr, int len)
{
    if(NULL == arr)
    {
        return -1;
    }

    if(len < 2)
    {
        return 0;
    }

    for(int gap = len/2; gap > 0; gap /= 2)
    {
        for(int grp = 0; grp < gap; ++grp)
        {
            for(int i = grp + gap; i < len; i += gap)
            {
                for(int j = i; j > grp; j -= gap)
                {
                    if(arr[j] < arr[j - gap])
                    {
                        swap_val(arr, j, j - gap);
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }

    return 0;
}

int set_random_val(int* arr, int len, bool same)
{
    if(NULL == arr)
    {
        return -1;
    }

    if(len < 1)
    {
        return 0;
    }

    srand(time(NULL));

    for(int i = 0; i < len; ++i)
    {
        arr[i] = i + 1;
    }

    for(int i = 0; i < len; ++i)
    {
        int change = random() % 2;
        if(change == 1)
        {
            if(same)
            {
                arr[i] = random() % len + 1;
            }
            else
            {
                int change_idx = random() % len;
                if(i != change_idx)
                {
                    swap_val(arr, i, change_idx);
                }
            }
        }
    }

    return 0;
}

void print_arr(int* arr, int len)
{
    if(NULL == arr || len < 1)
    {
        return;
    }

    for(int i = 0; i < len; ++i)
    {
        cout<<arr[i]<<" ";
    }

    cout<<endl;
}

const int ARR_LEN = 100;

int main(int, char**)
{
    int arr[ARR_LEN] = {0};

    for(int i = 0; i < 2; ++i)
    {
        set_random_val(arr, ARR_LEN, (bool)i);
        print_arr(arr, ARR_LEN);

        //selection_sort(arr, ARR_LEN);
        // bubble_sort(arr, ARR_LEN);
        // insertion_sort(arr, ARR_LEN);
        shell_sort(arr, ARR_LEN);
        print_arr(arr, ARR_LEN);
    }

    return 0;
}
