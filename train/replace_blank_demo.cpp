/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-11-30
* Descript: 
*
============================================================================*/

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

void replace_blank(const char* ori)
{
    if(NULL == ori)
    {
        return;
    }

    int len = 0;
    int blank_num = 0;
    int i = 0;
    while(ori[i] != '\0')
    {
        if(' ' == ori[i])
        {
            ++blank_num;
        }

        ++len;
        ++i;
    }

    if(len == 0)
    {
        cout<<"empty str!"<<endl;
        return;
    }

    int new_len = len + 2 * blank_num;
    char* arr = new char[new_len + 1];
    arr[new_len-1] = '\0';
    --len;
    --new_len;

    while(len >= 0 && new_len >= 0)
    {
        if(ori[len] == ' ')
        {
            arr[new_len--] = '0';
            arr[new_len--] = '2';
            arr[new_len--] = '%';
            --len;
        }
        else
        {
            arr[new_len--] = ori[len--];
        }
    }

    cout<<arr<<endl;
    delete[] arr;
}

int main(int, char**)
{
    char buf[BUFSIZ] = {0};
    while(true)
    {
        memset(buf, 0, BUFSIZ);
        cin.getline(buf, BUFSIZ);
        string str(buf);
        if("q" == str)
        {
            return 0;
        }
        
        replace_blank(str.c_str());        
    }

    return 0;
}
