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

    void ReverseList();

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
void CList<T>::ReverseList()
{
    ListNode<T>* pNode = m_pHead;
    ListNode<T>* pPre = NULL;

    while(pNode != NULL)
    {
        ListNode<T>* pNext = pNode->m_pNext;
        if(pNext == NULL)
        {
            m_pHead = pNode;
        }

        pNode->m_pNext = pPre;
        pPre = pNode;
        pNode = pNext;
    }
}

int main(int, char**)
{
    CList<int> li;
    for(int i = 0; i < 10; ++i)
    {
        li.PushBack(i);
    }

    li.Print();

    li.ReverseList();

    li.Print();

    return 0;
}
