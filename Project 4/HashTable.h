#ifndef HASHTABLE_INCLUDED
#define HASHTABLE_INCLUDED

#include <string>
#include <list>
#include "support.h"
using namespace std;

class HashTable
{
public:
    HashTable(int size);
    ~HashTable();
    void insert(const Sequence& seq);
    bool get(const string& key, size_t& offset);
private:
    list<Sequence>* m_table; // dynamically allocated array of lists of Sequences
    int m_size;
    int hash(const string& key); // hash function
};

#endif // HASHTABLE_INCLUDED