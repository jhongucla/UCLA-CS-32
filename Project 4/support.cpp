#include "support.h"
#include <iostream>
#include <fstream>
using namespace std;

bool getInt(istream& inf, int& n)
{
    char ch;
    if (!inf.get(ch)  ||  !isascii(ch)  ||  !isdigit(ch))
        return false;
    inf.unget();
    inf >> n;
    return true;
}

bool getCommand(istream& inf, char& cmd, int& length, int& offset)
{
    if (!inf.get(cmd)  ||  (cmd == '\n'  &&  !inf.get(cmd)) )
    {
        cmd = 'x';  // signals end of file
        return true;
    }
    char ch;
    switch (cmd)
    {
        case 'A':
            return getInt(inf, length) && inf.get(ch) && ch == ':';
        case 'C':
            return getInt(inf, length) && inf.get(ch) && ch == ',' && getInt(inf, offset);
    }
    return false;
}

// deltaCopy determines how long a match goes on when given a match
// and writes a copy instruction to the delta file
void deltaCopy(ostream& deltaf, const string& oldFile, const string& newFile,
               size_t& j, size_t offset, int seqLen)
{
    size_t matchLen = seqLen; // we know the match is at least as long as the sequence
    while (offset+matchLen < oldFile.size() && j+matchLen < newFile.size()
           && oldFile[offset+matchLen] == newFile[j+matchLen])
        matchLen++;
    deltaf << "C" << matchLen << "," << offset;
    j += matchLen;
}