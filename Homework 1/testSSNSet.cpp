#include "SSNSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    SSNSet s;
    assert(s.size() == 0);
    unsigned long x = 1234;
    s.add(x);
    assert(!s.add(1234));
    assert(s.size() == 1);
    s.add(2345);
    assert(s.size() == 2);
    cout << "Passed all tests" << endl;
    s.print();
}
