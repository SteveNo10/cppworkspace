/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-18
* Descript: 
*
============================================================================*/

#include <iostream>

using namespace std;

class BinaryTreeNode
{
public:
    BinaryTreeNode(int nVal)
        : m_nVal(nVal), m_pLeft(NULL), m_pRight(NULL)
    {

    }

public:
    int m_nVal;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};

BinaryTreeNode* CreateTree(int idx, int* arr, int len)
{
    if(idx >= len)
    {
        return NULL;
    }

    BinaryTreeNode* pNode = new BinaryTreeNode(arr[idx]);
    pNode->m_pLeft = CreateTree(2 * idx + 1, arr, len);
    pNode->m_pRight = CreateTree(2 * idx + 2, arr, len);
    return pNode;
}

void PrintTreePre(BinaryTreeNode* pHead)
{
    cout<<pHead->m_nVal<<" ";

    if(pHead->m_pLeft != NULL)
    {
        PrintTreePre(pHead->m_pLeft);
    }

    if(pHead->m_pRight != NULL)
    {
        PrintTreePre(pHead->m_pRight);
    }
}

void PrintTreePreOut(BinaryTreeNode* pHead)
{
    if(pHead != NULL)
    {
        PrintTreePre(pHead);
    }

    cout<<endl;
}

void Mirror(BinaryTreeNode* pHead)
{
    if(pHead != NULL)
    {
        BinaryTreeNode* pTmp = pHead->m_pLeft;
        pHead->m_pLeft = pHead->m_pRight;
        pHead->m_pRight = pTmp;
        Mirror(pHead->m_pLeft);
        Mirror(pHead->m_pRight);
    }
}

int main(int, char**)
{
    int arr[10] = {8, 4, 5, 1, 2, 6, 7, 3, 9};
    BinaryTreeNode* pOri = CreateTree(0, arr, 10);
    PrintTreePreOut(pOri);

    Mirror(pOri);
    PrintTreePreOut(pOri);

    return 0;
}
