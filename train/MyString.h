/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-12-07
* Descript: 
*
============================================================================*/

#ifndef __MYSTRING_H__
#define __MYSTRING_H__

#include <string.h>

class CMyString
{
public:
    CMyString(const char* str = NULL);
    ~CMyString();

    CMyString(const CMyString& o);
    CMyString& operator=(const CMyString& o);
    
    int Length() const;
    const char* Data() const;

private:
    char* m_data;
};

#endif
