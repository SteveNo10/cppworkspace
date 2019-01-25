/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-24
* Descript: 
*
============================================================================*/

#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

void Init(int* arr, int row, int col, int mine_num)
{
    if(NULL == arr || row < 1 || col < 1 || mine_num > row * col)
    {
        return;
    }

    for(int i = 0; i < mine_num; ++i)
    {
        arr[i] = -1;
    }

    int len = row * col;
    for(int i = len-1; i >= 0; --i)
    {
        int randnum = random()%(i+1);
        if(randnum != i)
        {
            int tmp = arr[i];
            arr[i] = arr[randnum];
            arr[randnum] = tmp;
        }
    }

    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            if(arr[i*col+j] == -1)
            {
                continue;
            }

            int count = 0;
            for(int x = i-1; x <= i+1; ++x)
            {
                if(x < 0 || x >= row)
                {
                    continue;
                }

                for(int y = j-1; y <= j+1; ++y)
                {
                    if(y < 0 || y >= col)
                    {
                        continue;
                    }

                    if(x == i && y == j)
                    {
                        continue;
                    }

                    if(arr[x*col+y] == -1)
                    {
                        ++count;
                    }
                }
            }

            arr[i*col+j] = count;
        }
    }

    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            int tmp = arr[i*col+j];
            if(tmp == -1)
            {
                cout<<"* ";
            }
            else
            {
                cout<<tmp<<" ";
            }
        }
        cout<<endl;
    }
}

int main(int, char**)
{
    srand(time(NULL));

    int arr[100] = {0};
    Init(arr, 10, 10, 20);

    return 0;
}
