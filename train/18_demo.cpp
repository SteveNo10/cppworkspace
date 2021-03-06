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

bool IsEqual(BinaryTreeNode* pOri, BinaryTreeNode* pDst)
{
    if(pDst == NULL)
    {
        return true;
    }

    if(pOri != NULL)
    {
        if(pOri->m_nVal == pDst->m_nVal)
        {
            if(IsEqual(pOri->m_pLeft, pDst->m_pLeft) && IsEqual(pOri->m_pRight, pDst->m_pRight))
            {
                return true;
            }
        }
    }

    return false;
}

bool IsContains(BinaryTreeNode* pOri, BinaryTreeNode* pDst)
{
    bool bContains = false;

    if(pOri != NULL && pDst != NULL)
    {
        if(pOri->m_nVal == pDst->m_nVal)
        {
            bContains = IsEqual(pOri, pDst);
        }

        if(!bContains)
        {
            bContains = IsContains(pOri->m_pLeft, pDst);
        }

        if(!bContains)
        {
            bContains = IsContains(pOri->m_pRight, pDst);
        }
    }

    return bContains;
}

int main(int, char**)
{
    int arr[10] = {8, 4, 5, 1, 2, 6, 7, 3, 9};
    BinaryTreeNode* pOri = CreateTree(0, arr, 10);
    PrintTreePreOut(pOri);

    // int arrDst[4] = {4, 1, 2, 3};
    int arrDst[5] = {4, 1, 2, 3, 9};
    BinaryTreeNode* pDst = CreateTree(0, arrDst, 5);
    PrintTreePreOut(pDst);

    if(IsContains(pOri, pDst))
    {
        cout<<"yes"<<endl;
    }
    else
    {
        cout<<"no"<<endl;
    }

    return 0;
}
