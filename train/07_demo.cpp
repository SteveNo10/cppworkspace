/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-14
* Descript: 
*
============================================================================*/

#include <iostream>
#include <stack>
#include <queue>
#include <exception>
#include <string>

using namespace std;

template <typename T>
class CQueue
{
public:
    CQueue();
    ~CQueue();

    void appendTail(const T& node);
    T deleteHead();

private:
    stack<T> stack1;
    stack<T> stack2;
};

template <typename T>
CQueue<T>::CQueue()
{

}

template <typename T>
CQueue<T>::~CQueue()
{

}

template <typename T>
void CQueue<T>::appendTail(const T& node)
{
    stack1.push(node);
}

template <typename T>
T CQueue<T>::deleteHead()
{
    if(stack2.empty())
    {
        while(!stack1.empty())
        {
            stack2.push(stack1.top());
            stack1.pop();
        }
    }

    if(stack2.empty())
    {
        throw string("empty queue");
    }

    T res = stack2.top();
    stack2.pop();

    return res;
}

template <typename T>
class CStack
{
public:
    CStack();
    ~CStack();

    void Push(T val);
    T Pop();

private:
    queue<T> queue1;
    queue<T> queue2;
};

template <typename T>
CStack<T>::CStack()
{

}

template <typename T>
CStack<T>::~CStack()
{

}

template <typename T>
void CStack<T>::Push(T val)
{
    if(!queue2.empty())
    {
        queue2.push(val);
    }
    else
    {
        queue1.push(val);
    }
}

template <typename T>
T CStack<T>::Pop()
{
    T res;
    if(!queue1.empty() && queue2.empty())
    {
        while(queue1.size() != 1)
        {
            queue2.push(queue1.front());
            queue1.pop();
        }

        res = queue1.front();
        queue1.pop();
    }
    else if(!queue2.empty() && queue1.empty())
    {
        while(queue2.size() != 1)
        {
            queue1.push(queue2.front());
            queue2.pop();
        }

        res = queue2.front();
        queue2.pop();
    }
    else
    {
        throw string("exception");
    }

    return res;
}

int main(int, char**)
{
    CQueue<int> que;
    que.appendTail(1);
    que.appendTail(2);
    que.appendTail(3);
    que.appendTail(4);

    cout<<que.deleteHead()<<endl;
    cout<<que.deleteHead()<<endl;

    que.appendTail(5);
    que.appendTail(6);

    cout<<que.deleteHead()<<endl;
    cout<<que.deleteHead()<<endl;
    cout<<que.deleteHead()<<endl;
    cout<<que.deleteHead()<<endl;
    // cout<<que.deleteHead()<<endl;
    
    CStack<int> sta;
    sta.Push(6);
    sta.Push(5);
    sta.Push(2);
    sta.Push(1);
    cout<<sta.Pop()<<endl;
    cout<<sta.Pop()<<endl;
    sta.Push(4);
    sta.Push(3);
    cout<<sta.Pop()<<endl;
    cout<<sta.Pop()<<endl;
    cout<<sta.Pop()<<endl;
    cout<<sta.Pop()<<endl;

    return 0;
}
