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

void swap(int* arr, int idx1, int idx2)
{
    int tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;
}

void selection_sort(int* arr, int len)
{
    for(int i = 0; i < len - 1; ++i)
    {
        int min_idx = i;
        for(int j = i; j < len; ++j)
        {
            if(arr[min_idx] > arr[j])
            {
                min_idx = j;
            }
        }

        if(min_idx != i)
        {
            swap(arr, i, min_idx);
        }
    }
}

void bubble_sort(int* arr, int len)
{
    for(int i = len-1; i > 0; --i)
    {
        for(int j = 0; j < i; ++j)
        {
            if(arr[j] > arr[j+1])
            {
                swap(arr, j, j+1);
            }
        }
    }
}

void insertion_sort(int* arr, int len)
{
    for(int i = 1; i < len; ++i)
    {
        for(int j = i; j > 0; --j)
        {
            if(arr[j] < arr[j-1])
            {
                swap(arr, j, j-1);
            }
        }
    }
}

void shell_sort(int* arr, int len)
{
    for(int gap = len/2; gap > 0; gap/=2)
    {
        for(int group = 0; group < gap; ++group)
        {
            for(int i = group + gap; i < len; i+=gap)
            {
                for(int j = i; j > group; j-=gap)
                {
                    if(arr[j] < arr[j-gap])
                    {
                        swap(arr, j, j-gap);
                    }
                }
            }
        }
    }
}

void merge(int* arr, int begin, int mid, int end, int* tmp)
{
    int low = begin;
    int high = mid + 1;
    int k = begin;
    while(low <= mid && high <= end)
    {
        if(arr[low] < arr[high])
        {
            tmp[k++] = arr[low++];
        }
        else
        {
            tmp[k++] = arr[high++];
        }
    }

    while(low <= mid)
    {
        tmp[k++] = arr[low++];
    }

    while(high <= end)
    {
        tmp[k++] = arr[high++];
    }

    for(k = begin; k <= end; ++k)
    {
        arr[k] = tmp[k];
    }
}

void merge_sort(int* arr, int begin, int end, int* tmp)
{
    if(begin >= end)
    {
        return;
    }

    int mid = begin + (end - begin) / 2;
    merge_sort(arr, begin, mid, tmp);
    merge_sort(arr, mid+1, end, tmp);
    merge(arr, begin, mid, end, tmp);
}

void heap_adjust(int* arr, int n, int len)
{
    int max_idx = n;
    int left = 2 * n + 1;
    int right = left + 1;

    while(left < len && arr[left] > arr[max_idx])
    {
        max_idx = left;
    }

    while(right < len && arr[right] > arr[max_idx])
    {
        max_idx = right;
    }

    if(max_idx != n)
    {
        swap(arr, n, max_idx);
        heap_adjust(arr, max_idx, len);
    }
}

void heap_build(int* arr, int len)
{
    for(int i = len / 2; i >= 0; --i)
    {
        heap_adjust(arr, i, len);
    }
}

void heap_sort(int* arr, int len)
{
    heap_build(arr, len);

    for(int i = len - 1; i > 0; --i)
    {
        swap(arr, 0, i);
        heap_adjust(arr, 0, i);
    }
}

void quick_sort(int* arr, int begin, int end)
{
    if(begin >= end)
    {
        return;
    }

    int idx = begin;
    int left = begin;
    int right = end;
    while(left < right)
    {
        while(left < right && arr[right] >= arr[idx])
        {
            --right;
        }

        while(left < right && arr[left] <= arr[idx])
        {
            ++left;
        }

        swap(arr, left, right);
    }

    swap(arr, idx, left);
    quick_sort(arr, begin, left - 1);
    quick_sort(arr, left + 1, end);
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
                    swap(arr, i, change_idx);
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

        // selection_sort(arr, ARR_LEN);
        // bubble_sort(arr, ARR_LEN);
        // insertion_sort(arr, ARR_LEN);
        // shell_sort(arr, ARR_LEN);
        // int tmp[ARR_LEN] = {0};
        // merge_sort(arr, 0, ARR_LEN - 1, tmp);
        // heap_sort(arr, ARR_LEN);
        quick_sort(arr, 0, ARR_LEN -1);
        print_arr(arr, ARR_LEN);
    }

    return 0;
}
