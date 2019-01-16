/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-16
* Descript: 
*
============================================================================*/

#include <iostream>

using namespace std;

template <typename T>
class ListNode
{
public:
    ListNode(T val);

public:
    T m_nVal;
    ListNode<T>* m_pNext;    
};

template <typename T>
ListNode<T>::ListNode(T val)
    : m_nVal(val), m_pNext(NULL)
{

}

template <typename T>
class CList
{
public:
    CList();
    ~CList();

    void PushBack(T val);
    void Print();
    ListNode<T>* FindKBack(int k);

private:
    ListNode<T>* m_pHead;
};

template <typename T>
CList<T>::CList()
    : m_pHead(NULL)
{

}

template <typename T>
CList<T>::~CList()
{
    ListNode<T>* m_pTmp = m_pHead;
    ListNode<T>* m_pDel = m_pTmp;
    while(m_pTmp != NULL)
    {
        m_pDel = m_pTmp;
        m_pTmp = m_pTmp->m_pNext;
        delete m_pDel;
    }

    m_pHead = NULL;
}

template <typename T>
void CList<T>::PushBack(T val)
{
    ListNode<T>* pNode = new ListNode<T>(val);
    if(m_pHead == NULL)
    {
        m_pHead = pNode;
    }
    else
    {
        ListNode<T>* pTmp = m_pHead;
        while(pTmp->m_pNext != NULL)
        {
            pTmp = pTmp->m_pNext;
        }

        pTmp->m_pNext = pNode;
    }
}

template <typename T>
void CList<T>::Print()
{
    ListNode<T>* pTmp = m_pHead;
    while(pTmp != NULL)
    {
        cout<<pTmp->m_nVal<<" ";
        pTmp = pTmp->m_pNext;
    }

    cout<<endl;
}

template <typename T>
ListNode<T>* CList<T>::FindKBack(int k)
{
    if(m_pHead == NULL || k <= 0)
    {
        return 0;
    }

    ListNode<T>* pTmp = m_pHead;
    int i = 0;
    while(pTmp != NULL && i < k)
    {
        pTmp = pTmp->m_pNext;
        ++i;
    }

    if(i < k)
    {
        return NULL;
    }

    ListNode<T>* pTmpHead = m_pHead;
    while(pTmp != NULL)
    {
        pTmp = pTmp->m_pNext;
        pTmpHead = pTmpHead->m_pNext;
    }

    return pTmpHead;
}

int main(int, char**)
{
    CList<int> li;
    for(int i = 0; i < 10; ++i)
    {
        li.PushBack(i);
    }

    for(int i = 0; i < 12; ++i)
    {
        ListNode<int>* pNode = li.FindKBack(i);
        if(NULL == pNode)
        {
            cout<<"not found!"<<endl;
        }
        else
        {
            cout<<"found:"<<pNode->m_nVal<<endl;
        }
    }

    return 0;
}
