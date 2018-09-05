/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-09-05
* Descript: 
*
============================================================================*/

#include <iostream>

using namespace std;

class CA
{
public:
    CA(int ia, int ib) : a(ia), b(ib)
    {

    }

    inline bool operator==(const CA& ca) const;

private:
    int a;
    int b;
};

inline bool CA::operator==(const CA& ca) const
{
    if(a == ca.a && b == ca.b)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(int, char**)
{
    CA a1(10, 20);
    CA a2(10, 20);
    CA a3(10, 30);

    if(a1 == a2)
    {
        cout<<"a1 == a2"<<endl;
    }
    else
    {
        cout<<"a1 != a2"<<endl;
    }

    if(a2 == a3)
    {
        cout<<"a2 == a3"<<endl;
    }
    else
    {
        cout<<"a2 != a3"<<endl;
    }

    return 0;
}
