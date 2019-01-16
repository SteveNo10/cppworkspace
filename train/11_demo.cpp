/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-16
* Descript: 
*
============================================================================*/

#include <iostream>
#include <math.h>

using namespace std;

const double PRECISION = 0.000001;
bool g_invalid;

bool DoubleEqualZero(double d)
{
    if(d < PRECISION && d > -PRECISION)
    {
        return true;
    }

    return false;
}

double Compute(double base, unsigned int exponet)
{
    if(exponet == 0)
    {
        return 1.0;
    }
    else if(exponet == 1)
    {
        return base;
    }

    double res = Compute(base, exponet >> 1);
    res *= res;
    if((exponet & 0x1) == 1)
    {
        res *= base;
    }

    return res;
}

double Power(double base, int exponet)
{
    g_invalid = false;
    if(DoubleEqualZero(base) && exponet < 0)
    {
        g_invalid = true;
        return 0.0;
    }

    bool bNegitave = exponet >= 0 ? false : true;

    unsigned int uexponet = bNegitave ? -exponet : exponet;
    double res = Compute(base, uexponet);
    if(bNegitave)
    {
        res = 1.0 / res;
    }

    return res;
}

int main(int, char**)
{
    double base;
    int exponet;

    while(true)
    {
        cin>>base;
        cin>>exponet;
        cout<<Power(base, exponet)<<endl;
        cout<<pow(base, exponet)<<endl;
    }

    return 0;
}
