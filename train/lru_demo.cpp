/*============================================================================
 * Copyright (C) 2019 Ltd. All rights reserved.
 * Author  : SteveNo10
 * Time    : 2019-01-21
 * Descript: 
 *
 ============================================================================*/

#include <list>
#include <unordered_map>
#include <iostream>
#include <assert.h>

using namespace std;

class LRUCache 
{
public:
    LRUCache(int capacity) 
    {
        m_capacity = capacity;
    }

    int get(int key) 
    {
        int val = -1;
        auto itr = m_hashmap.find(key);
        if(itr != m_hashmap.end())
        {
            val = itr->second->second;
            m_list.splice(m_list.begin(), m_list, itr->second);
        }

        return val;
    }

    void put(int key, int value) 
    {
        auto itr = m_hashmap.find(key);
        if(itr != m_hashmap.end())
        {
            itr->second->second = value;
            m_list.splice(m_list.begin(), m_list, itr->second);
        }
        else
        {
            if((int)m_hashmap.size() == m_capacity)
            {
                m_hashmap.erase(m_list.back().first);
                m_list.pop_back();
            }

            m_list.push_front(make_pair(key, value));
            m_hashmap.insert(make_pair(key, m_list.begin()));
        }
    }

private:
    int m_capacity;
    list<pair<int, int>> m_list;
    unordered_map<int, list<pair<int, int>>::iterator> m_hashmap;
};

int main(int, char**)
{
    LRUCache cache = LRUCache( 2 /* 缓存容量 */ );

    cache.put(1, 1);
    cache.put(2, 2);
    assert(1 == cache.get(1));       // 返回  1
    cache.put(3, 3);    // 该操作会使得密钥 2 作废
    assert(-1 == cache.get(2));       // 返回 -1 (未找到)
    cache.put(4, 4);    // 该操作会使得密钥 1 作废
    assert(-1 == cache.get(1));       // 返回 -1 (未找到)
    assert(3 == cache.get(3));       // 返回  3
    assert(4 == cache.get(4));       // 返回  4

    return 0;
}
