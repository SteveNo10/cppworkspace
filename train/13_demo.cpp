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
    void DeleteNode(ListNode<T>* pToBeDeleted);
    ListNode<T>* Find(T val);

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

template<typename T>
void CList<T>::DeleteNode(ListNode<T>* pToBeDeleted)
{
    if(NULL == m_pHead || NULL == pToBeDeleted)
    {
        return;
    }

    if(m_pHead == pToBeDeleted)
    {
        m_pHead = m_pHead->m_pNext;
        delete pToBeDeleted;
    }
    else if(pToBeDeleted->m_pNext == NULL)
    {
        ListNode<T>* pPre = m_pHead;
        while(pPre != NULL)
        {
            if(pPre->m_pNext == pToBeDeleted)
            {
                break;
            }

            pPre = pPre->m_pNext;
        }

        pPre->m_pNext = pToBeDeleted->m_pNext;
        delete pToBeDeleted;
    }
    else
    {
        ListNode<T>* pTrueDelete = pToBeDeleted->m_pNext;
        pToBeDeleted->m_nVal = pTrueDelete->m_nVal;
        pToBeDeleted->m_pNext = pTrueDelete->m_pNext;
        delete pTrueDelete;
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

    ListNode<int>* pF1 = li.Find(0);
    li.DeleteNode(pF1);
    li.Print();

    ListNode<int>* pF2 = li.Find(2);
    li.DeleteNode(pF2);
    li.Print();
    
    ListNode<int>* pF3 = li.Find(9);
    li.DeleteNode(pF3);
    li.Print();

    ListNode<int>* pF4 = li.Find(6);
    li.DeleteNode(pF4);
    li.Print();

    ListNode<int>* pF5 = li.Find(5);
    li.DeleteNode(pF5);
    li.Print();

    ListNode<int>* pF6 = li.Find(1);
    li.DeleteNode(pF6);
    li.Print();

    ListNode<int>* pF7 = li.Find(4);
    li.DeleteNode(pF7);
    li.Print();

    ListNode<int>* pF8 = li.Find(3);
    li.DeleteNode(pF8);
    li.Print();

    ListNode<int>* pF9 = li.Find(7);
    li.DeleteNode(pF9);
    li.Print();

    ListNode<int>* pF10 = li.Find(8);
    li.DeleteNode(pF10);
    li.Print();
    return 0;
}
