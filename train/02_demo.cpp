/*============================================================================
* Copyright (C) 2019 Ltd. All rights reserved.
* Author  : SteveNo10
* Time    : 2019-01-12
* Descript: 
*
============================================================================*/

#include <iostream>
#include <pthread.h>

using namespace std;

class SingletonLazy
{
private:
    SingletonLazy();
    SingletonLazy(const SingletonLazy& obj);
    SingletonLazy& operator=(const SingletonLazy& obj);

public:
    static SingletonLazy* GetInstance();

    void Print();

private:
    static SingletonLazy* m_pSingletonLazy;
    static pthread_mutex_t m_mutex;
};

SingletonLazy* SingletonLazy::m_pSingletonLazy = NULL;
pthread_mutex_t SingletonLazy::m_mutex = PTHREAD_MUTEX_INITIALIZER;

SingletonLazy::SingletonLazy()
{

}

void SingletonLazy::Print()
{
    cout<<"this is SingletonLazy!"<<endl;
}

SingletonLazy* SingletonLazy::GetInstance()
{
    if(m_pSingletonLazy == NULL)
    {
        pthread_mutex_lock(&m_mutex);
        if(m_pSingletonLazy == NULL)
        {
            m_pSingletonLazy = new SingletonLazy();
        }
        pthread_mutex_unlock(&m_mutex);
    }

    return m_pSingletonLazy;
}

class SingletonHungry
{
private:
    SingletonHungry();
    SingletonHungry(const SingletonHungry& obj);
    SingletonHungry& operator=(const SingletonHungry& obj);

public:
    static SingletonHungry* GetInstance();

    void Print();

private:
    static SingletonHungry* m_pSingletonHungry;
};

SingletonHungry* SingletonHungry::m_pSingletonHungry = new SingletonHungry();

SingletonHungry::SingletonHungry()
{

}

void SingletonHungry::Print()
{
    cout<<"this is SingletonHungry!"<<endl;
}

SingletonHungry* SingletonHungry::GetInstance()
{
    return m_pSingletonHungry;
}

int main(int, char**)
{
    SingletonLazy::GetInstance()->Print();
    SingletonHungry::GetInstance()->Print();

    return 0;
}
