/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-12
* Descript: 
*
============================================================================*/

#include <iostream>
#include <string.h>

using namespace std;

class MyString
{
public:
    MyString(const char* pData = NULL);
    ~MyString();
    MyString(const MyString& oStr);
    MyString& operator=(const MyString& oStr);

    friend ostream& operator<<(ostream& os, const MyString& oStr);

private:
    char* m_pData;
};

ostream& operator<<(ostream& os, const MyString& oStr)
{
    os<<oStr.m_pData<<endl;
    return os;
}

MyString::MyString(const char* pData)
{
    if(NULL == pData)
    {
        m_pData = new char[1];
        m_pData[0] = '\0';
    }
    else
    {
        int len = strlen(pData);
        m_pData = new char[len + 1];
        strncpy(m_pData, pData, len);
    }
}

MyString::~MyString()
{
    if(m_pData != NULL)
    {
        delete[] m_pData;
        m_pData = NULL;
    }
}

MyString::MyString(const MyString& oStr)
{
    int len = strlen(oStr.m_pData);
    m_pData = new char[len + 1];
    strncpy(m_pData, oStr.m_pData, len);
}

MyString& MyString::operator=(const MyString& oStr)
{
    /*
    if(&oStr != this)
    {
        MyString tmp(oStr);
        char* pTmp = m_pData;
        m_pData = tmp.m_pData;
        tmp.m_pData = pTmp;
    }
    */

    if(&oStr != this)
    {
        delete[] m_pData;
        m_pData = NULL;

        m_pData = new char[strlen(oStr.m_pData) + 1];
        strcpy(m_pData, oStr.m_pData);
    }

    return *this;
}

int main(int, char**)
{
    MyString a("Hello");
    MyString b = "World";
    MyString c(a);
    MyString d = b;

    cout<<a<<b<<c<<d;

    return 0;
}
