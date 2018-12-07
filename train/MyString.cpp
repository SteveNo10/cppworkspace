/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-12-07
* Descript: 
*
============================================================================*/

#include "MyString.h"

CMyString::CMyString(const char* str)
{
    if(NULL == str)
    {
        m_data = new char[1];
        m_data[0] = '\0';
    }
    else
    {
        int len = strlen(str);
        m_data = new char[len + 1];
        strncpy(m_data, str, len);
    }
}

CMyString::~CMyString()
{
    if(NULL != m_data)
    {
        delete[] m_data;
        m_data = NULL;
    }
}

CMyString::CMyString(const CMyString& o)
{
    int len = strlen(o.m_data);
    m_data = new char[len + 1];
    strncpy(m_data, o.m_data, len);
}

CMyString& CMyString::operator=(const CMyString& o)
{
    if(this != &o)
    {
        CMyString tmp(o);

        char* pTmp = tmp.m_data;
        tmp.m_data = m_data;
        m_data = pTmp;
    }

    /*
    if(this != &o)
    {
        delete[] m_data;
        int len = strlen(o.m_data);
        m_data = new char[len + 1];
        strncpy(m_data, o.m_data, len);
    }
    */

    return *this;
}

int CMyString::Length() const
{
    return strlen(m_data);
}

const char* CMyString::Data() const
{
    return m_data;
}
