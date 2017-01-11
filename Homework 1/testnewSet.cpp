#include "newSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Set s(2);
    assert(s.empty());
    ItemType x = 9876543;
    assert( !s.get(42, x)  &&  x == 9876543); // x unchanged by get failure
    s.insert(123456789);
    assert(s.size() == 1);
    assert(s.get(0, x)  &&  x == 123456789);
    ItemType y = 1234;
    s.insert(y);
    assert(s.size() == 2);
    assert(s.contains(1234));
    assert(!s.contains(2345));
    ItemType z;
    assert(s.get(1, z));
    assert(!s.get(5, z));
    assert(!s.insert(12345));
    assert(s.erase(1234));
    assert(!s.erase(123));
    s.insert(1234);
    assert(s.size() == 2);
    Set q(5);
    q.insert(1);
    q.insert(2);
    q.insert(3);
    q.insert(4);
    q.insert(5);
    assert(!q.insert(6));
    s.dump();
    cout << endl;
    q.dump();
    cout << endl;
    s.swap(q);
    s.dump();
    cout << endl;
    q.dump();
    cout << endl;
    assert(!s.insert(1));
    assert(!q.insert(1));
    s = q;
    s.dump();
    cout << "Passed all tests" << endl;
}
