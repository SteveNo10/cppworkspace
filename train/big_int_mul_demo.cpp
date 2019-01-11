/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-12-10
* Descript: 
*
============================================================================*/

#include <string.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

void swap(char* arr, int a, int b)
{
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

void reverse(char* arr, int len)
{
    for(int i = 0, j = len-1; i < j; ++i, --j)
    {
        swap(arr, i, j);
    }
}

char* big_int_mul(char* str1, char* str2, char* str3)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    str3 = new char[len1 + len2];
    memset(str3, '0', len1 + len2);

    int* tmp = new int[len1+len2];
    for(int i = 0; i < len1+len2; ++i)
    {
        tmp[i] = 0;
    }
    
    reverse(str1, len1);
    reverse(str2, len2); 

    for(int i = 0; i < len1; ++i)
    {
        for(int j = 0; j < len2; ++j)
        {
            char a = str1[i] - '0';
            char b = str2[j] - '0';
            tmp[i+j] += a*b;
        }
    }

    for(int i = 0; i < (len1 + len2); ++i)
    {
        tmp[i+1] += tmp[i] / 10;
        tmp[i] = tmp[i] % 10;
        cout<<tmp[i]<<endl;
        str3[i] = (char)(tmp[i]) + '0';
    }

    delete[] tmp;

    reverse(str3, len1 + len2);

    return str3;
}

int main(int, char**)
{
    char str1[] = "12345";
    char str2[] = "67891";
    char* str3 = NULL;

    int a1 = atoi(str1);
    int a2 = atoi(str2);
    cout<<a1*a2<<endl;

    big_int_mul(str1, str2, str3);
    cout<<str3<<endl;

    return 0;
}
