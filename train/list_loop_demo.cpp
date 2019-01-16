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
    ListNode<T>* Find(T val);
    bool IsLoop();

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
ListNode<T>* CList<T>::Find(T val)
{
    ListNode<T>* m_pTmp = m_pHead;
    while(m_pTmp != NULL)
    {
        if(m_pTmp->m_nVal == val)
        {
            return m_pTmp;
        }

        m_pTmp = m_pTmp->m_pNext;
    }

    return NULL;
}

template <typename T>
bool CList<T>::IsLoop()
{
    if(m_pHead == NULL)
    {
        return false;
    }

    ListNode<T>* pFast = m_pHead;
    ListNode<T>* pSlow = m_pHead;

    while(pFast != NULL && pFast->m_pNext != NULL && pSlow != NULL)
    {
        pSlow = pSlow->m_pNext;
        pFast = pFast->m_pNext->m_pNext;

        if(pSlow == pFast)
        {
            return true;
        }
    }

    return false;
}

int main(int, char**)
{
    CList<int> li;
    for(int i = 0; i < 10; ++i)
    {
        li.PushBack(i);
    }

    li.Print();

    if(li.IsLoop())
    {
        cout<<"Loop"<<endl;        
    }
    else
    {
        cout<<"Not Loop"<<endl;
    }

    ListNode<int>* p9 = li.Find(9);
    ListNode<int>* p6 = li.Find(6);
    p9->m_pNext = p6;

    if(li.IsLoop())
    {
        cout<<"Loop"<<endl;
    }
    else
    {
        cout<<"Not Loop"<<endl;
    }

    return 0;
}
