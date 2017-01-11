#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
    Set s;
    assert(s.empty());
    ItemType x = 1234;
    assert( !s.get(42, x)  &&  x == 1234); // x unchanged by get failure
    s.insert(12345);
    assert(s.size() == 1);
    assert(s.get(0, x)  &&  x == 12345);
    assert(s.contains(12345));
    assert(!s.contains(1234));
    s.insert(23456);
    assert(s.size() == 2);
    ItemType y = 123;
    ItemType z = 234;
    assert(s.get(0, y) && (y == 12345 || y == 23456));
    assert(s.get(0, z) && y == z);
    Set q;
    q.insert(34567);
    assert(q.size() == 1);
    s.swap(q);
    assert(s.size() == 1 && q.size() == 2);
    q.dump();
    cout << "Passed all tests" << endl;
}
