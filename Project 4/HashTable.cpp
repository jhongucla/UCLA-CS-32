#include <list>
#include <string>
#include <iostream>
#include "HashTable.h"
#include "support.h"
using namespace std;

HashTable::HashTable(int size)
: m_size(size)
{
    m_table = new list<Sequence>[size];
}

HashTable::~HashTable()
{
    delete[] m_table;
}

void HashTable::insert(const Sequence& seq)
{
    int index = hash(seq.m_seq);
    if (m_table[index].empty()) // if the bucket at the array index is empty, add the Sequence
    {
        m_table[index].push_back(seq);
        return;
    }
    bool found = false;
    for (Sequence getSeq : m_table[index])
        if (getSeq.m_seq == seq.m_seq)
        {
            found = true;
            break;
        }
    if (!found) // if the bucket at the array index isn't empty, but it doesn't contain the Sequence, add it
        m_table[index].push_back(seq);
}

bool HashTable::get(const string& key, size_t& offset)
{
    int index = hash(key);
    if (m_table[index].empty())
        return false;
    for (Sequence getSeq : m_table[index])
    {
        if (getSeq.m_seq == key) // if the Sequence is found, set offset to the offset of the Sequence
        {
            offset = getSeq.m_offset;
            return true;
        }
    }
    return false;
}

int HashTable::hash(const string &key) // hash function computes an array index from the key
{
    unsigned int hash = 2166136261u; // FNV-1a hash function
    for (int k = 0; k < key.size(); k++)
    {
        hash += key[k];
        hash *= 16777619;
    }
    return hash % m_size; // mods hash by size of array and returns an array index
}