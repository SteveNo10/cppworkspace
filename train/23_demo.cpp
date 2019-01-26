/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-26
* Descript: 
*
============================================================================*/

#include <iostream>
#include <list>

using namespace std;

class BinaryTreeNode
{
public:
    BinaryTreeNode(int val) : m_nValue(val), m_pLeft(NULL), m_pRight(NULL) { };

    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};

void PrintLevel(BinaryTreeNode* pHead)
{
    if(pHead == NULL)
    {
        return;
    }

    list<BinaryTreeNode*> li;
    li.push_back(pHead);

    while(!li.empty())
    {
        BinaryTreeNode* pNode = li.front();
        li.pop_front();
        cout<<pNode->m_nValue<<" ";
        if(pNode->m_pLeft != NULL)
        {
            li.push_back(pNode->m_pLeft);
        }

        if(pNode->m_pRight != NULL)
        {
            li.push_back(pNode->m_pRight);
        }
    }

    cout<<endl;
}

int main(int, char**)
{
    BinaryTreeNode* pHead = new BinaryTreeNode(8);
    pHead->m_pLeft = new BinaryTreeNode(6);
    pHead->m_pRight = new BinaryTreeNode(10);
    pHead->m_pLeft->m_pLeft = new BinaryTreeNode(5);
    pHead->m_pLeft->m_pRight = new BinaryTreeNode(7);
    pHead->m_pRight->m_pLeft = new BinaryTreeNode(9);
    pHead->m_pRight->m_pRight = new BinaryTreeNode(11);

    PrintLevel(pHead);

    return 0;
}
