/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-11-06
* Descript: 
*
============================================================================*/

#include <iostream>

using namespace std;

class Empty
{
};

class EmptyVir
{
public:
    virtual ~EmptyVir();
};

int main(int, char**)
{
    cout<<"sizeof(Empty):"<<sizeof(Empty)<<endl;

    Empty* pEmpty = NULL;
    cout<<"sizeof(Empty*)"<<sizeof(pEmpty)<<endl;

    cout<<"sizeof(EmptyVir):"<<sizeof(EmptyVir)<<endl;

    cout<<"sizeof(int):"<<sizeof(int)<<endl;

    return 0;
}
