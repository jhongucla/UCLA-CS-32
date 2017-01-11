#include "Set.h"
#include <iostream>

using namespace std;

Set::Set()
{
    m_size = 0;
    m_head = nullptr; // indicates list is empty
}

Set::~Set()
{
    if (!empty()) // destructor only called on a non empty list
    {
        Node* iterator = m_head;
        while (iterator != nullptr) // iterates through every node of list
        {
            Node* toDelete = iterator; // creates temp pointer to node to delete
            iterator = iterator->m_next;
            delete toDelete;
        }
    }
}

Set::Set(const Set& other)
{
    m_head = nullptr;
    m_size = 0; // creates an empty list
    ItemType toCopy;
    for (int i = 0; i < other.size(); i++)
    {
        other.get(i, toCopy); // gets every value from other list and inserts into list
        insert(toCopy);
    }
}

Set& Set::operator=(const Set& rhs)
{
    if (this != &rhs) // copy and swap idiom for assignment operator 
    {
        Set temp(rhs);
        swap(temp);
    }
    return *this;
}

bool Set::empty() const
{
    return m_head == nullptr;
}

int Set::size() const
{
    return m_size;
}

bool Set::insert(const ItemType& value)
{
    if (!contains(value)) // only inserts value if the list doesn't already contain the value
    {
        Node* toInsert = new Node;
        toInsert->m_value = value;
        toInsert->m_next = m_head; // links new value to the front of the list
        toInsert->m_prev = nullptr;
        if (!empty()) // if there are already values in the list, link the first value to the new value
            m_head->m_prev = toInsert;
        m_head = toInsert; // make the head the new value
        m_size++;
        return true;
    }
    return false;
}

bool Set::erase(const ItemType& value)
{
    if (contains(value)) // only erases if the value is in the list
    {
        if (size() == 1) // if the only value in list is the value to erase
        {
            delete m_head;
            m_head = nullptr;
        }
        else
        {
            Node* toErase = m_head;
            while (toErase->m_value != value) // traverse the list until toErase points to the value to erase
                toErase = toErase->m_next;
            if (toErase == m_head)
            {
                m_head->m_next->m_prev = nullptr; // make the node after toErase the new head
                m_head = m_head->m_next;
                delete toErase;
            }
            else
            {
                toErase->m_prev->m_next = toErase->m_next; // link the nodes before and after toErase together
                if (toErase->m_next != nullptr) // if toErase isn't the last node, link previous pointers
                    toErase->m_next->m_prev = toErase->m_prev;
                delete toErase;
            }
        }
        m_size--;
        return true;
    }
    return false;
}

bool Set::contains(const ItemType& value) const
{
    if (!empty()) // only a non empty list can contain a value
    {
        for (Node* p = m_head; p != nullptr; p = p->m_next) // traverse the entire list
            if (p->m_value == value) // if the value is found
                return true;
    }
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    if (i >= 0 && i < size()) // check whether i satisfies conditions
    {
        Node* toGet = m_head;
        for (int j = 0; j < i; j++) // traverse list to the i+1-th node
            toGet = toGet->m_next;
        value = toGet->m_value; // store the i+1-th node's value in value
        return true;
    }
    return false;
}

void Set::swap(Set& other)
{
    int tempSize = size(); // create temp variable to store this set's size
    Node* temp_m_head = m_head; // create temp pointer variable to point to this set's head
    
    m_size = other.size(); // set this set's size to the other set's size
    m_head = other.m_head; // set this set's head pointer to point to the other set's head
    
    other.m_size = tempSize; // set the other set's size to this set's size
    other.m_head = temp_m_head; // set the other set's head pointer to point to this set's head
}

void Set::dump() const
{
    Node* p;
    cerr << m_head->m_value << endl;
    for (p = m_head; p->m_next != nullptr; p = p->m_next)
        cerr << p->m_next->m_value << endl;
    cerr << endl;
    for (; p != nullptr; p = p->m_prev)
        cerr << p->m_value << endl;
    cerr << endl;
}

void unite(const Set& s1, const Set& s2, Set& result)
{
    Set tempSet = s1; // create a copy of s1
    for (int i = 0; i < s2.size(); i++)
    {
        ItemType value;
        s2.get(i, value); // get every value from s2
        tempSet.insert(value); // attempt to insert value into copy of s1
    }
    result = tempSet; // set result to the copy of s1
}

void subtract(const Set& s1, const Set& s2, Set& result)
{
    Set tempSet; // create a temp empty set
    for (int i = 0; i < s1.size(); i++)
    {
        ItemType value;
        s1.get(i, value); // get every value from s1
        if (!s2.contains(value)) // if s2 doesn't contain the value, insert the value into the temp set
            tempSet.insert(value);
    }
    result = tempSet; // set result to the temp set
}


