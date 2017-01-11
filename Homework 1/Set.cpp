#include "Set.h"
#include <iostream>

using namespace std;

Set::Set()
{
    m_size = 0;
}

bool Set::empty() const
{
    return m_size == 0;
}

int Set::size() const
{
    return m_size;
}

bool Set::insert(const ItemType& value)
{
    if (!contains(value) && m_size < DEFAULT_MAX_ITEMS)
    {
        m_set[m_size] = value;
        m_size++;
        return true;
    }
    return false;
}

bool Set::erase(const ItemType& value)
{
    if (empty())
        return false;
    if (contains(value))
    {
        if (size() == 1)
        {
            m_size--;
            return true;
        }
        else
        {
            for (int i = 0; i < m_size; i++)
            {
                if (m_set[i] == value)
                {
                    m_set[i] = m_set[m_size-1];
                    m_size--;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Set::contains(const ItemType& value) const
{
    if (empty())
        return false;
    for (int i = 0; i < m_size; i++)
    {
        if (m_set[i] == value)
            return true;
    }
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    if (i >= 0 && i < size())
    {
        value = m_set[i];
        return true;
    }
    return false;
}

void Set::swap(Set& other)
{
    int tempSize = size();
    m_size = other.size();
    other.m_size = tempSize;
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        ItemType tempValue = m_set[i];
        m_set[i] = other.m_set[i];
        other.m_set[i] = tempValue;
    }
}

void Set::dump() const
{
    for (int i = 0; i < m_size; i++)
        cerr << m_set[i] << endl;
}