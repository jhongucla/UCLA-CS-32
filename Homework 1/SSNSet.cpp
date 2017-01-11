#include "SSNSet.h"
#include <iostream>
using namespace std;

SSNSet::SSNSet()
:m_ssnset()
{}

bool SSNSet::add(unsigned long ssn)
{
    return m_ssnset.insert(ssn);
}

int SSNSet::size() const
{
    return m_ssnset.size();
}

void SSNSet::print() const
{
    for (int i = 0; i < m_ssnset.size(); i++)
    {
        unsigned long value;
        m_ssnset.get(i, value);
        cout << value << endl;
    }
}