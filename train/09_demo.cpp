/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-15
* Descript: 
*
============================================================================*/

#include <iostream>

using namespace std;

int Fibonacci(int n)
{
    if(n == 0)
    {
        return 0;
    }
    else if(n == 1)
    {
        return 1;
    }
    else
    {
        return Fibonacci(n-1) + Fibonacci(n-2);
    }
}

int FibonacciQuick(int n)
{
    int result[2] = {0, 1};
    if(n < 2)
    {
        return result[n];
    }

    int fibone = 0;
    int fibtwo = 1;
    int fibN = 0;
    for(int i = 2; i <= n; ++i)
    {
        fibN = fibone + fibtwo;
        fibone = fibtwo;
        fibtwo = fibN;
    }

    return fibN;
}

int main(int, char**)
{
    cout<<Fibonacci(10)<<endl;
    cout<<FibonacciQuick(10)<<endl;
    
    return 0;
}
