// Scaffold.cpp

#include "provided.h"
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const; 
    void display() const; 
    bool makeMove(int column, int color); 
    int undoMove();
  private:
    int m_nColumns;
    int m_nLevels;
    vector<vector<int>> m_scaffold;
    stack<int> m_history; // store a history of moves on the scaffold
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
: m_nColumns(nColumns), m_nLevels(nLevels)
{
    if (nColumns <= 0 || nLevels <= 0) // check that columns and levels are positive
    {
        cerr << "Columns and levels need to be positive." << endl;
        exit(1);
    }
    m_scaffold.resize(m_nLevels);
    for (int i = 0; i < m_nLevels; i++)
        m_scaffold[i].resize(m_nColumns);
    for (int i = 0; i < m_nLevels; i++) // make every position on the scaffold vacant
        for (int j = 0; j < m_nColumns; j++)
            m_scaffold[i][j] = VACANT;
}

int ScaffoldImpl::cols() const
{
    return m_nColumns;
}

int ScaffoldImpl::levels() const
{
    return m_nLevels;
}

int ScaffoldImpl::numberEmpty() const
{
    return (int)(m_nColumns*m_nLevels-m_history.size()); // total number of positions minus number of checkers on scaffold
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    if (column < 1 || column > m_nColumns || level < 1 || level > m_nLevels)
        return VACANT;
    return m_scaffold[level-1][column-1];
}

void ScaffoldImpl::display() const
{
    for (int i = m_nLevels-1; i >= 0; i--)
    {
        cout << '|';
        for (int j = 0; j < m_nColumns; j++)
        {
            char checker;
            switch(m_scaffold[i][j]) // display the correct character depending on value in scaffold
            {
                case RED:
                    checker = 'R';
                    break;
                case BLACK:
                    checker = 'B';
                    break;
                default:
                    checker = ' ';
            }
            cout << checker << '|';
        }
        cout << endl;
    }
    cout << '+';
    for (int k = 0; k < m_nColumns; k++)
        cout << '-' << '+';
    cout << endl;
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    if (column < 1 || column > m_nColumns || (color != RED && color != BLACK))
        return false;
    for (int i = 0; i < m_nLevels; i++)
    {
        if (m_scaffold[i][column-1] == VACANT) // find the first empty spot in a column
        {
            m_scaffold[i][column-1] = color;
            m_history.push(column); // record the move in the history member
            return true;
        }
    }
    return false;
}

int ScaffoldImpl::undoMove()
{
    if (m_history.empty()) // if there is no history, then the scaffold is empty
        return 0;
    int lastCol = m_history.top();
    m_history.pop();
    for (int i = m_nLevels-1; i >= 0; i--)
    {
        if (m_scaffold[i][lastCol-1] != VACANT) // find the highest level in the column that has a checker 
        {
            m_scaffold[i][lastCol-1] = VACANT;
            break;
        }
    }
    return lastCol;
}

//******************** Scaffold functions *******************************

// These functions simply delegate to ScaffoldImpl's functions.
// You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
