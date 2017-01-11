#include "History.h"
#include "globals.h"
#include <iostream>

using namespace std;

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            hist[i][j] = 0;
        }
    }
}

bool History::record(int r, int c)
{
    if (r <= 0 || r > m_rows || c <= 0 || c > m_cols)
        return false;
    hist[r-1][c-1]++;
    return true;
}

void History::display() const
{
    clearScreen();
    char disp[MAXROWS][MAXCOLS];
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            if (hist[i][j] == 0)
                disp[i][j] = '.';
            else if (hist[i][j] >= 26)
                disp[i][j] = 'Z';
            else
                disp[i][j] = hist[i][j] + 64;
        }
    }
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            cout << disp[i][j];
        }
        cout << endl;
    }
    cout << endl;
}


