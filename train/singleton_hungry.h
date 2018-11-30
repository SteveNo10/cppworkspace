/*============================================================================
* Copyright (C) 2018 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2018-11-12
* Descript: 
*
============================================================================*/

#ifndef __SINGLETON_HUNGRY_H__
#define __SINGLETON_HUNGRY_H__

class CSingletonHungry
{
public:
    static CSingletonHungry* get_instance();

    void print();

private:
    CSingletonHungry();
    CSingletonHungry(const CSingletonHungry&);
    CSingletonHungry& operator=(const CSingletonHungry&);

private:
    static CSingletonHungry* m_instance;
};

#endif
