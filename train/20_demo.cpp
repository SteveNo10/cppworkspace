/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-23
* Descript: 
*
============================================================================*/

#include <iostream>
#include <iomanip>

using namespace std;

void Print(int* arr, int row, int col)
{
    if(NULL == arr || row < 1 || col < 1)
    {
        return;
    }

    int level = min((row-1)/2, (col-1)/2);
    for(int start = 0; start <= level; ++start)
    {
        int endi = row - start - 1;
        int endj = col - start - 1;

        for(int i = start; i <= endj; ++i)
        {
            cout<<arr[start*col+i]<<" ";
        }

        if(start < endi)
        {
            for(int i = start + 1; i <= endi; ++i)
            {
                cout<<arr[i*col + endj]<<" ";
            }
        }

        if(start < endi && start < endj)
        {
            for(int i = endj - 1; i >= start; --i)
            {
                cout<<arr[endi*col + i]<<" ";
            }
        }

        if(start < endi - 1 && start < endj)
        {
            for(int i = endi - 1; i > start; --i)
            {
                cout<<arr[i*col + start]<<" ";
            }
        }
    }

    cout<<endl;
}

const int row = 36;
const int col = 1;
const int num = row * col;

int main(int, char**)
{
    int arr[num];
    for(int i = 0; i < num; ++i)
    {
        arr[i] = i + 1;
    }
    
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            cout<<setw(2)<<arr[i*col+j]<<" ";
        }

        cout<<endl;
    }

    Print(arr, row, col);

    return 0;
}
