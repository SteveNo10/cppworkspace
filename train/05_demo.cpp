/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-14
* Descript: 
*
============================================================================*/

#include <iostream>

using namespace std;

class ListNode
{
public:
    ListNode(int val);

public:
    int m_val;
    ListNode* m_pNext;
};

ListNode::ListNode(int val)
    : m_val(val), m_pNext(NULL)
{

}

class List
{
public:
    List();
    ~List();

    void PushBack(int val);
    void PushFront(int val);

    void Print();
    void PrintReverse();

private:
    void PrintReverse(ListNode* pNode);

private:
    ListNode* m_pHead;
};

List::List()
    : m_pHead(NULL)
{

}

List::~List()
{
    if(m_pHead == NULL)
    {
        return;
    }

    ListNode* pTmp = m_pHead;
    ListNode* pNext = pTmp->m_pNext;
    while(pNext != NULL)
    {
        delete pTmp;
        pTmp = pNext;
        pNext = pTmp->m_pNext;
    }

    delete pTmp;
}

void List::PushBack(int val)
{
    ListNode* pNode = new ListNode(val);
    if(m_pHead == NULL)
    {
        m_pHead = pNode;
    }
    else
    {
        ListNode* pTmp = m_pHead;
        while(pTmp->m_pNext != NULL)
        {
            pTmp = pTmp->m_pNext;
        }

        pTmp->m_pNext = pNode;
    }
}

void List::Print()
{
    if(m_pHead == NULL)
    {
        return;
    }

    ListNode* pTmp = m_pHead;
    while(pTmp->m_pNext != NULL)
    {
        cout<<pTmp->m_val<<"->";
        pTmp = pTmp->m_pNext;
    }

    cout<<pTmp->m_val<<endl;
}

void List::PrintReverse()
{
    PrintReverse(m_pHead);
}

void List::PrintReverse(ListNode* pNode)
{
    if(pNode == NULL)
    {
        return;
    }

    if(pNode->m_pNext != NULL)
    {
        PrintReverse(pNode->m_pNext);
    }

    if(pNode == m_pHead)
    {
        cout<<pNode->m_val<<endl;
    }
    else
    {
        cout<<pNode->m_val<<"->";
    }
}

int main(int, char**)
{
    List li;
    for(int i = 0; i < 10; ++i)
    {
        li.PushBack(i);
    }

    li.Print();

    li.PrintReverse();

    return 0;
}
