/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-14
* Descript: 
*
============================================================================*/

#include <iostream>
#include <string>

using namespace std;

void ReplaceSpacing(char* ori, int len)
{
    if(ori == NULL || len <= 0)
    {
        return;
    }

    int ori_idx = 0;
    int ori_len = 0;
    int spacing_num = 0;
    while(ori[ori_idx++] != '\0')
    {
        if(ori[ori_idx - 1] == ' ')
        {
            ++spacing_num;
        }

        ++ori_len;
    }

    int dst_len = ori_len + spacing_num * 2;
    if(dst_len + 1 > len)
    {
        return;
    }

    ori_idx = ori_len - 1;
    int dst_idx = dst_len - 1;

    while(ori_idx >= 0 && dst_idx > ori_idx)
    {
        if(ori[ori_idx] == ' ')
        {
            ori[dst_idx--] = '0';
            ori[dst_idx--] = '2';
            ori[dst_idx--] = '%';
            --ori_idx;
        }
        else
        {
            ori[dst_idx--] = ori[ori_idx--];
        }
    }
}

int main(int, char**)
{
    char str[50] = "We are Happy.";
    ReplaceSpacing(str, 50);
    cout<<str<<endl;

    return 0;
}
