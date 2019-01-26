/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-26
* Descript: 
*
============================================================================*/

#include <iostream>
#include <stack>
#include <stdlib.h>
#include <time.h>

using namespace std;

class MyStack
{
public:
    MyStack();
    ~MyStack();

    void push(int val);
    void pop();
    int min();
    int top();

private:
    stack<int> m_data;
    stack<int> m_min;
};

MyStack::MyStack()
{

}

MyStack::~MyStack()
{

}

void MyStack::push(int val)
{
    if(!m_min.empty())
    {
        if(val < m_min.top())
        {
            m_min.push(val);
        }
        else
        {
            m_min.push(m_min.top());
        }
    }
    else
    {
        m_min.push(val);
    }

    m_data.push(val);
}

int MyStack::top()
{
    return m_data.top();
}

int MyStack::min()
{
    return m_min.top();
}

void MyStack::pop()
{
    m_min.pop();
    m_data.pop();
}

void Print(int* arr, int num)
{
    for(int i = 0; i < num; ++i)
    {
        cout<<arr[i]<<" ";
    }

    cout<<endl;
}

int main(int, char**)
{
    srand(time(NULL));
    const int num = 10;
    int arr[num] = {0};
    for(int i = 0; i < num; ++i)
    {
        arr[i] = i + 1;
    }

    Print(arr, num);

    for(int i = num-1; i>=0; --i)
    {
        int swapnum = rand()%(i+1);
        if(swapnum != i)
        {
            int tmp = arr[i];
            arr[i] = arr[swapnum];
            arr[swapnum] = tmp;
        }
    }

    Print(arr, num);

    MyStack mystack;
    for(int i = 0; i < num; ++i)
    {
        mystack.push(arr[i]);
        cout<<mystack.top()<<" ";
        cout<<mystack.min()<<" ";
    }

    cout<<endl;

    return 0;
}
