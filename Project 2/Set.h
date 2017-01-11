#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>

typedef std::string ItemType;

const int DEFAULT_MAX_ITEMS = 100;

class Set
{
    
public:
    Set();
    
    ~Set();
    
    Set(const Set& other);
    
    Set& operator=(const Set& rhs);
    
    bool empty() const;
    
    int size() const;
    
    bool insert(const ItemType& value);
    
    bool erase(const ItemType& value);
    
    bool contains(const ItemType& value) const;
    
    bool get(int i, ItemType& value) const;
    
    void swap(Set& other);
    
    void dump() const;
    
private:
    struct Node
    {
        ItemType m_value;
        Node* m_next;
        Node* m_prev;
    };
    
    int m_size;
    Node* m_head;
};

void unite(const Set& s1, const Set& s2, Set& result);

void subtract(const Set& s1, const Set& s2, Set& result);

#endif // SET_INCLUDED
