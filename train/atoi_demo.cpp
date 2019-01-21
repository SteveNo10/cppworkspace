/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-18
* Descript: 
*
============================================================================*/

#include <iostream>
#include <limits.h>

using namespace std;

// const int INT_MAX = 0xEFFFFFFF;
// const int INT_MIN = 0xFFFFFFFF;

class Solution 
{
public:
    int myAtoi(string str) 
    {
        if(str.empty())
        {
            return 0;
        }

        unsigned int begin = 0;
        while(str[begin] == ' ')
        {
            ++begin;
        }

        if(begin == str.size())
        {
            return 0;
        }

        bool bNegative = false;
        if(str[begin] == '+')
        {
            ++begin;    
        }
        else if(str[begin] == '-')
        {
            bNegative = true;
            ++begin;
        }

        unsigned int num = 0;
        long val = 0;
        while(begin < str.size())
        {
            if(str[begin] < '0' || str[begin] > '9')
            {
                break;
            }

            int tmp = str[begin] - '0';
            val = val * 10 + tmp;
            if(bNegative)
            {
                if(-val < INT_MIN)
                {
                    return INT_MIN;
                }
            }
            else
            {
                if(val > INT_MAX)
                {
                    return INT_MAX;
                }
            }
            ++num;
            ++begin;
        }

        if(num == 0)
        {
            return 0;
        }

        return bNegative ? -val : val;
    }
};

int main(int, char**)
{
    Solution so;
    string str;
    while(true)
    {
        cin>>str;
        cout<<so.myAtoi(str)<<endl;
    }
}
