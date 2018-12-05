/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-12-05
* Descript: 
*
============================================================================*/

#include <string>

using namespace std;

string StrAdd(string str1, string str2)
{
    return str1 + str2;
}

int IntAdd(int a, int b)
{
    return a + b;
}

void StrAddTest()
{
    string str1 = "Hello ";
    string str2 = "World!";
    for(int i = 0; i < 10000000; ++i)
    {
        string str = StrAdd(str1, str2);
    }
}

void IntAddTest()
{
    int j = 0;
    for(int i = 0; i < 100000000; ++i)
    {
        j = IntAdd(i, i+1);
    }
}

int main(int, char**)
{
    StrAddTest();
    IntAddTest();

    return 0;
}
