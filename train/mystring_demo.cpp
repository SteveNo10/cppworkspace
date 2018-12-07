/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-12-07
* Descript: 
*
============================================================================*/

#include "MyString.h"
#include <iostream>

using namespace std;

int main(int, char**)
{
    CMyString str1;
    CMyString str2("Hello");
    CMyString str3("World");
    CMyString str4(str3);

    str1 = str2;

    cout<<str1.Data()<<endl;
    cout<<str2.Data()<<endl;
    cout<<str3.Data()<<endl;
    cout<<str4.Data()<<endl;

    return 0;
}
