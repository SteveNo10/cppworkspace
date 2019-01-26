/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-26
* Descript: 
*
============================================================================*/

#include <iostream>
#include <stack>

using namespace std;

bool IsPushPop(int* arr_push, int* arr_pop, int len)
{
    if(arr_push == NULL || arr_pop == NULL || len <= 0)
    {
        return false;
    }

    stack<int> st;
    int push_idx = 0;
    int pop_idx = 0;

    while(push_idx <= len && pop_idx < len)
    {
        int pop_val = arr_pop[pop_idx];
        if(st.empty() || st.top() != pop_val)
        {
            if(push_idx < len)
            {
                st.push(arr_push[push_idx++]);
            }
            else
            {
                return false;
            }
        }
        else if(st.top() == pop_val)
        {
            ++pop_idx;
            st.pop();
        }
    }

    return true;
}

int main(int, char**)
{
    const int num = 5;
    int arr_push[num] = {1, 2, 3, 4, 5};
    // int arr_pop[num] = {4, 5, 3, 2, 1};
    int arr_pop[num] = {4, 3, 5, 1, 2};

    if(IsPushPop(arr_push, arr_pop, num))
    {
        cout<<"Yes"<<endl;
    }
    else
    {
        cout<<"No"<<endl;
    }

    return 0;
}
