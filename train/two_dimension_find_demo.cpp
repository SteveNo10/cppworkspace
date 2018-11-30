/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-11-30
* Descript: 
*
============================================================================*/

#include <iostream>
#include <string>

using namespace std;

const int COL = 4;
const int ROW = 4;

bool find_arr(int arr[][COL], int val)
{
    bool bFound = false;
    int row = 1;
    int col = COL;
    while(row <= ROW && col > 0)
    {
        if(arr[row-1][col-1] == val)
        {
            cout<<"find row:"<<row<<" col:"<<col<<endl;
            bFound = true;
            --col;
            ++row;
        }
        else if(arr[row-1][col-1] > val)
        {
            --col;
        }
        else
        {
            ++row;
        }
    }

    return bFound;
}

int main(int, char**)
{
    int arr[ROW][COL] = {{1, 2, 8, 9}, {2, 4, 9, 12}, {4, 7, 10, 13}, {6, 8, 11, 15}};

    string str;
    while(true)
    {
        cin>>str;
        if(str == "q")
        {
            return 0;
        }

        int val = atoi(str.c_str());

        if(!find_arr(arr, val))
        {
            printf("not found\n");
        }
    }

    return 0;
}
