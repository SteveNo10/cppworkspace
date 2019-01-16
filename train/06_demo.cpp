/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-14
* Descript: 
*
============================================================================*/

#include <iostream>
#include <queue>

using namespace std;

class TreeNode
{
public:
    TreeNode(int val);
    ~TreeNode();

public:
    int m_val;
    TreeNode* m_left;
    TreeNode* m_right;
};

TreeNode::TreeNode(int val)
    : m_val(val), m_left(NULL), m_right(NULL)
{

}

class SearchBinaryTree
{
public:
    SearchBinaryTree();
    ~SearchBinaryTree();

public:
    void Add(int val);
    void PreOrder();
    void MidOrder();
    void PostOrder();
    void LevelOrder();
    void ConCreate(int* pPre, int* pMid, int len);

private:
    void Add(TreeNode** pNode, int val);
    void PreOrder(TreeNode* pNode);
    void MidOrder(TreeNode* pNode);
    void PostOrder(TreeNode* pNode);
    TreeNode* ConCreate(int* pPre, int nPreBegin, int nPreEnd, int* pMid, int nMidBegin, int nMidEnd);

private:
    TreeNode* m_root;
};

SearchBinaryTree::SearchBinaryTree()
    : m_root(NULL)
{

}

SearchBinaryTree::~SearchBinaryTree()
{

}

void SearchBinaryTree::ConCreate(int* pPre, int* pMid, int len)
{
    if(pPre == NULL || pMid == NULL || len <= 0)
    {
        return;
    }

    m_root = ConCreate(pPre, 0, len - 1, pMid, 0, len - 1);
}

TreeNode* SearchBinaryTree::ConCreate(int* pPre, int nPreBegin, int nPreEnd, int* pMid, int nMidBegin, int nMidEnd)
{
    int val = pPre[nPreBegin];
    TreeNode* pNode = new TreeNode(val);
    int idx = nMidBegin;
    for(; idx <= nMidEnd; ++idx)
    {
        if(pMid[idx] == val)
        {
            break;
        }
    }

    if(idx > nMidBegin)
    {
        pNode->m_left = ConCreate(pPre, nPreBegin + 1, nPreBegin + (idx - nMidBegin), pMid, nPreBegin, idx - 1);
    }

    if(idx < nMidEnd)
    {
        pNode->m_right = ConCreate(pPre, nPreBegin + (idx - nMidBegin) + 1, nPreEnd, pMid, idx + 1, nMidEnd);
    }

    return pNode;
}

void SearchBinaryTree::Add(TreeNode** pNode, int val)
{
    if(*pNode == NULL)
    {
        *pNode = new TreeNode(val);
    }
    else
    {
        if((*pNode)->m_val > val)
        {
            Add(&((*pNode)->m_left), val);
        }
        else
        {
            Add(&((*pNode)->m_right), val);
        }
    }
}

void SearchBinaryTree::Add(int val)
{
    Add(&m_root, val);
}

void SearchBinaryTree::PreOrder(TreeNode* pNode)
{
    if(pNode != NULL)
    {
        cout<<pNode->m_val<<" ";
        PreOrder(pNode->m_left);
        PreOrder(pNode->m_right);
    }
}

void SearchBinaryTree::PreOrder()
{
    PreOrder(m_root);
    cout<<endl;
}

void SearchBinaryTree::MidOrder(TreeNode* pNode)
{
    if(pNode != NULL)
    {
        MidOrder(pNode->m_left);
        cout<<pNode->m_val<<" ";
        MidOrder(pNode->m_right);
    }
}

void SearchBinaryTree::MidOrder()
{
    MidOrder(m_root);
    cout<<endl;
}

void SearchBinaryTree::PostOrder(TreeNode* pNode)
{
    if(pNode != NULL)
    {
        PostOrder(pNode->m_left);
        PostOrder(pNode->m_right);
        cout<<pNode->m_val<<" ";
    }
}

void SearchBinaryTree::PostOrder()
{
    PostOrder(m_root);
    cout<<endl;
}

void SearchBinaryTree::LevelOrder()
{
    if(m_root != NULL)
    {
        queue<TreeNode*> que;
        que.push(m_root);
        
        while(!que.empty())
        {
            TreeNode* pTmp = que.front();
            que.pop();
            cout<<pTmp->m_val<<" ";
            if(pTmp->m_left != NULL)
            {
                que.push(pTmp->m_left);
            }

            if(pTmp->m_right != NULL)
            {
                que.push(pTmp->m_right);
            }
        }
        
        cout<<endl;
    }
}

int main(int, char**)
{
    SearchBinaryTree sbt;
    int arr[10] = {3, 5, 6, 7, 1, 9, 2, 4, 8, 0};
    for(int i = 0; i < 10; ++i)
    {
        sbt.Add(arr[i]);
    }

    sbt.PreOrder();
    sbt.MidOrder();
    sbt.PostOrder();
    sbt.LevelOrder();

    SearchBinaryTree sbt2;
    int arrPre[10] = {3, 1, 0, 2, 5, 4, 6, 7, 9, 8};
    int arrMid[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};    
    sbt2.ConCreate(arrPre, arrMid, 10);
    sbt2.PostOrder();

    return 0;
}
