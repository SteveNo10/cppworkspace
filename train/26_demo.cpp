/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-30
* Descript: 
*
============================================================================*/

#include <iostream>

using namespace std;

class ComplexListNode
{
public:
    ComplexListNode(int nVal) : m_nVal(nVal), m_pNext(NULL), m_pSibling(NULL) { };

    int m_nVal;
    ComplexListNode* m_pNext;
    ComplexListNode* m_pSibling;
};

void Print(ComplexListNode* pHead)
{
    while(pHead != NULL)
    {
        cout<<pHead->m_nVal<<":"<<(pHead->m_pSibling == NULL ? 0 : pHead->m_pSibling->m_nVal)<<" ";
        pHead = pHead->m_pNext;
    }
    cout<<endl;
}

ComplexListNode* Copy(ComplexListNode* pHead)
{
    if(pHead == NULL)
    {
        return NULL;
    }

    ComplexListNode* pNode = pHead;
    ComplexListNode* pNext = pHead;
    while(pNode != NULL)
    {
        pNext = pNode->m_pNext;
        pNode->m_pNext = new ComplexListNode(pNode->m_nVal);
        pNode->m_pNext->m_pNext = pNext;
        pNode = pNext;
    }

    pNode = pHead;
    while(pNode != NULL)
    {
        if(pNode->m_pSibling != NULL)
        {
            pNode->m_pNext->m_pSibling = pNode->m_pSibling->m_pNext;
        }
        pNode = pNode->m_pNext->m_pNext;
    }

    Print(pHead);

    pNode = pHead->m_pNext;
    pNext = pNode;
    while(pHead != NULL && pNode != NULL)
    {
        pHead->m_pNext = pNode->m_pNext;

        if(pNode->m_pNext == NULL)
        {
            break;
        }

        pNode->m_pNext = pHead->m_pNext->m_pNext;
        pHead = pHead->m_pNext;
        pNode = pHead->m_pNext;
    }
    
    return pNext;
}

int main(int, char**)
{
    ComplexListNode* pHead = new ComplexListNode(1);
    pHead->m_pNext = new ComplexListNode(2);
    pHead->m_pNext->m_pNext = new ComplexListNode(3);
    pHead->m_pNext->m_pNext->m_pNext = new ComplexListNode(4);
    pHead->m_pNext->m_pNext->m_pNext->m_pNext = new ComplexListNode(5);
    pHead->m_pSibling = pHead->m_pNext->m_pNext;
    pHead->m_pNext->m_pSibling = pHead->m_pNext->m_pNext->m_pNext->m_pNext;
    pHead->m_pNext->m_pNext->m_pNext->m_pSibling = pHead->m_pNext;

    Print(pHead);
    
    Print(Copy(pHead));

    return 0;
}
