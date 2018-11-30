/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-11-12
* Descript: 
*
============================================================================*/

#include "singleton_hungry.h"
#include <stdio.h>

CSingletonHungry::CSingletonHungry* m_instance = new CSingletonHungry();

CSingletonHungry::CSingletonHungry()
{

}

CSingletonHungry::CSingletonHungry(const CSingletonHungry& /*singleton*/)
{

}

CSingletonHungry& CSingletonHungry::operator=(const CSingletonHungry& /*singleton*/)
{

}

CSingletonHungry* get_instance()
{
    return m_instance;
}

void CSingletonHungry::print()
{
    printf("this is singleton hungry\n");
}
