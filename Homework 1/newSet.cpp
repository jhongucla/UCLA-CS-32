#include "newSet.h"
#include <iostream>

using namespace std;

Set::Set(const int size)
{
    m_maxsize = size;
    m_set = new ItemType[m_maxsize];
    m_currsize = 0;
}

Set::~Set()
{
    delete [] m_set;
}

Set::Set(const Set& other)
{
    m_maxsize = other.m_maxsize;
    m_currsize = other.m_currsize;
    m_set = new ItemType[m_maxsize];
    for (int i = 0; i < m_currsize; i++)
        m_set[i] = other.m_set[i];
}

Set& Set::operator=(const Set& rhs)
{
    if (this != &rhs)
    {
        Set temp(rhs);
        swap(temp);
    }
    return *this;
}

bool Set::empty() const
{
    return m_currsize == 0;
}

int Set::size() const
{
    return m_currsize;
}

bool Set::insert(const ItemType& value)
{
    if (!contains(value) && size() < m_maxsize)
    {
        m_set[size()] = value;
        m_currsize++;
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
            m_currsize--;
            return true;
        }
        else
        {
            for (int i = 0; i < size(); i++)
            {
                if (m_set[i] == value)
                {
                    m_set[i] = m_set[size()-1];
                    m_currsize--;
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
    for (int i = 0; i < size(); i++)
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
    int tempCurrSize = size();
    m_currsize = other.size();
    other.m_currsize = tempCurrSize;
    int tempMaxSize = m_maxsize;
    m_maxsize = other.m_maxsize;
    other.m_maxsize = tempMaxSize;
    ItemType* tempPtr = m_set;
    m_set = other.m_set;
    other.m_set = tempPtr;
}

void Set::dump() const
{
    for (int i = 0; i < size(); i++)
        cerr << m_set[i] << endl;
}