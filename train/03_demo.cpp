/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-13
* Descript: 
*
============================================================================*/

#include <iostream>
#include <assert.h>

using namespace std;

const int ROW = 4;
const int COL = 4;

bool Find(int arr[ROW][COL], int row, int col, int val)
{
    assert(arr != NULL);
    assert(row > 0 && col > 0);

    for(int i = 0, j = col - 1; i < row && j >= 0;)
    {
        int tmp = arr[i][j];
        if(val > tmp)
        {
            ++i;
        }
        else if(val < tmp)
        {
            --j;
        }
        else
        {
            cout<<val<<" in "<<i<<", "<<j<<endl;
            return true;
        }
    }

    cout<<"not found"<<endl;
    return false;
}

int main(int, char**)
{
    int arr[ROW][COL] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};

    int val = 0;
    while(true)
    {
        cin>>val;
        Find(arr, 4, 4, val);

        if(-1 == val)
        {
            break;
        }
    }

    return 0;
}
