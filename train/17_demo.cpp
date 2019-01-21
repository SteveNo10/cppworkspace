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
    ListNode<T>* GetHead();
    void MergeSortedList(ListNode<T>* pList1, ListNode<T>* pList2);
    ListNode<T>* MergeRecursion(ListNode<T>* pList1, ListNode<T>* pList2);
    void MergeSortedListRecursion(ListNode<T>* pList1, ListNode<T>* pList2);

private:
    ListNode<T>* m_pHead;
};

template <typename T>
ListNode<T>* CList<T>::GetHead()
{
    return m_pHead;
}

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
ListNode<T>* CList<T>::MergeRecursion(ListNode<T>* pList1, ListNode<T>* pList2)
{
    if(pList1 == NULL)
    {
        return pList2;
    }

    if(pList2 == NULL)
    {
        return pList1;
    }

    ListNode<T>* pMergeNode = NULL;
    if(pList1->m_nVal < pList2->m_nVal)
    {
        pMergeNode = pList1;
        pMergeNode->m_pNext = MergeRecursion(pList1->m_pNext, pList2);
    }
    else
    {
        pMergeNode = pList2;
        pMergeNode->m_pNext = MergeRecursion(pList1, pList2->m_pNext);
    }

    return pMergeNode;
}

template <typename T>
void CList<T>::MergeSortedList(ListNode<T>* pList1, ListNode<T>* pList2)
{
    if(pList1 == NULL)
    {
        m_pHead = pList1;
        return;
    }

    if(pList2 == NULL)
    {
        m_pHead = pList2;
        return;
    }

    if(pList1->m_nVal < pList2->m_nVal)
    {
        m_pHead = pList1;
        pList1 = pList1->m_pNext;
    }
    else
    {
        m_pHead = pList2;
        pList2 = pList2->m_pNext;
    }

    ListNode<T>* pMergeNode = m_pHead;
    while(pList1 != NULL && pList2 != NULL)
    {
        if(pList1->m_nVal < pList2->m_nVal)
        {
            pMergeNode->m_pNext = pList1;
            pList1 = pList1->m_pNext;
        }
        else
        {
            pMergeNode->m_pNext = pList2;
            pList2 = pList2->m_pNext;
        }

        pMergeNode = pMergeNode->m_pNext;
    }

    if(pList1 != NULL)
    {
        pMergeNode->m_pNext = pList1;
    }

    if(pList2 != NULL)
    {
        pMergeNode->m_pNext = pList2;
    }
}

template <typename T>
void CList<T>::MergeSortedListRecursion(ListNode<T>* pList1, ListNode<T>* pList2)
{
    m_pHead = MergeRecursion(pList1, pList2);
}

int main(int, char**)
{
    CList<int> li1;
    for(int i = 0; i < 10; i+=2)
    {
        li1.PushBack(i);
    }
    li1.Print();

    CList<int> li2;
    for(int i = 1; i < 10; i+=2)
    {
        li2.PushBack(i);
    }
    li2.Print();

    CList<int> li3;
    // li3.MergeSortedList(li1.GetHead(), li2.GetHead());
    li3.MergeSortedListRecursion(li1.GetHead(), li2.GetHead());    
    li3.Print();

    return 0;
}
