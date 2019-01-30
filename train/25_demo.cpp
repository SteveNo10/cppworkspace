/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-30
* Descript: 
*
============================================================================*/

#include <iostream>
#include <list>

using namespace std;

class BinaryTreeNode
{
public:
    BinaryTreeNode(int nVal) : m_nValue(nVal), m_pLeft(NULL), m_pRight(NULL) { };

    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};

void FindPath(BinaryTreeNode* pNode, int expectSum, list<int>& listPath, int& nSum)
{
    nSum += pNode->m_nValue;
    listPath.push_back(pNode->m_nValue);

    if(pNode->m_pLeft == NULL && pNode->m_pRight == NULL)
    {
        if(nSum == expectSum)
        {
            for(int val : listPath)
            {
                cout<<val<<" ";
            }
            cout<<endl;
        }
    }

    if(pNode->m_pLeft != NULL)
    {
        FindPath(pNode->m_pLeft, expectSum, listPath, nSum);
    }

    if(pNode->m_pRight != NULL)
    {
        FindPath(pNode->m_pRight, expectSum, listPath, nSum);
    }

    nSum -= pNode->m_nValue;
    listPath.pop_back();
}

void FindPath(BinaryTreeNode* pHead, int expectSum)
{
    if(NULL == pHead)
    {
        return;
    }

    list<int> listPath;
    int nSum = 0;

    FindPath(pHead, expectSum, listPath, nSum);
}

int main(int, char**)
{
    BinaryTreeNode* pHead = new BinaryTreeNode(10);
    pHead->m_pLeft = new BinaryTreeNode(5);
    pHead->m_pRight = new BinaryTreeNode(12);
    pHead->m_pLeft->m_pLeft = new BinaryTreeNode(4);
    pHead->m_pLeft->m_pRight = new BinaryTreeNode(7);

    FindPath(pHead, 22);

    return 0;
}
