#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <sstream>
#include "HashTable.h"
#include "support.h"
#include "Delta.h"
using namespace std;

void createDelta(istream& oldf, istream& newf, ostream& deltaf)
{
    ostringstream s = ostringstream(); // read oldfile and newfile into strings
    s << oldf.rdbuf();
    string oldFile = s.str();
    s.str("");
    s.clear();
    s << newf.rdbuf();
    string newFile = s.str();
    size_t oldSize = oldFile.size();

    int seqLen1 = SEQ_LEN_1;
    int seqLen2 = SEQ_LEN_2;
    int seqLen3 = SEQ_LEN_3;
    int seqLen4 = SEQ_LEN_4;
    
    // if the length of oldfile is shorter than any of the sequences, change all sequences
    // longer than the length to the length of oldfile
    if (oldSize < seqLen4)
        seqLen4 = (int) oldSize;
    if (oldSize < seqLen3)
        seqLen3 = (int) oldSize;
    if (oldSize < seqLen2)
        seqLen2 = (int) oldSize;
    if (oldSize < seqLen1)
        seqLen1 = (int) oldSize;

    // create 4 hash tables with the appropriate number of buckets
    HashTable sequences1(hashSize(oldSize, seqLen1));
    HashTable sequences2(hashSize(oldSize, seqLen2));
    HashTable sequences3(hashSize(oldSize, seqLen3));
    HashTable sequences4(hashSize(oldSize, seqLen4));
    
    for (size_t i = 0; i < oldSize-seqLen1; i++) // fill each hash table with the sequences from oldfile
        sequences1.insert(Sequence(oldFile.substr(i, seqLen1), i));
    for (size_t i = 0; i < oldSize-seqLen2; i++)
        sequences2.insert(Sequence(oldFile.substr(i, seqLen2), i));
    for (size_t i = 0; i < oldSize-seqLen3; i++)
        sequences3.insert(Sequence(oldFile.substr(i, seqLen3), i));
    for (size_t i = 0; i < oldSize-seqLen4; i++)
        sequences4.insert(Sequence(oldFile.substr(i, seqLen4), i));
    
    size_t j = 0;
    string addSeq; // to store a sequence of characters to be added to the newfile
    while (j < newFile.size())
    {
        size_t offset1 = 0;
        // check if the sequence starting at j is in the first hash table
        if (j < newFile.size()-seqLen1 && sequences1.get(newFile.substr(j, seqLen1), offset1))
        {
            if (!addSeq.empty()) // write add instruction with stored sequence before writing a copy instruction
            {
                deltaf << "A" << addSeq.size() << ":" << addSeq;
                addSeq.clear(); // clear the sequence of characters to be added
            }
            size_t offset2 = 0;
            // check if the longer sequence starting at j is in the second hash table
            if (j < newFile.size()-seqLen2 && sequences2.get(newFile.substr(j, seqLen2), offset2))
            {
                size_t offset3 = 0;
                // check if the even longer sequence starting at j is in the third hash table
                if (j < newFile.size()-seqLen3 && sequences3.get(newFile.substr(j, seqLen3), offset3))
                {
                    size_t offset4 = 0;
                    // check if the longest sequence starting at j is in the fourth hash table
                    if (j < newFile.size()-seqLen4 && sequences4.get(newFile.substr(j, seqLen4), offset4))
                    {
                        // write the copy instruction and increment j by the appropriate amount
                        deltaCopy(deltaf, oldFile, newFile, j, offset4, seqLen4);
                        continue; // start over checking sequences with j at the incremented position
                    }
                    deltaCopy(deltaf, oldFile, newFile, j, offset3, seqLen3);
                    continue;
                }
                deltaCopy(deltaf, oldFile, newFile, j, offset2, seqLen2);
                continue;
            }
            deltaCopy(deltaf, oldFile, newFile, j, offset1, seqLen1);
        }
        else // sequence starting at j is not in any hash table so add character at j to sequence to be added later
        {
            addSeq += newFile[j];
            j++; // increment j to the next character
        }
    }
    if (!addSeq.empty()) // if there are still characters to be added, write the final add instruction
        deltaf << "A" << addSeq.size() << ":" << addSeq;
}

bool applyDelta(istream& oldf, istream& deltaf, ostream& newf)
{
    ostringstream s = ostringstream();
    s << oldf.rdbuf();
    string oldFile = s.str(); // read oldfile into a string
    
    char cmd;
    int length = 0;
    int offset = 0;
    while (getCommand(deltaf, cmd, length, offset)) // keep getting commands until an error or end of file
    {
        if (length <= 0)
            return false;
        switch (cmd)
        {
            case 'A': // if command is an add instruction, get the length number of characters and add to newfile
                char ch;
                for (int i = 0; i < length; i++)
                {
                    if (!deltaf.get(ch)) // if the end of the file is reached when characters expected, return false
                        return false;
                    newf << ch;
                }
                break;
            case 'C': // if command is a copy instruction, copy the length number of characters at offset to newfile
                if (offset+length > oldFile.size() || offset < 0) // if the offset is out of range, return false
                    return false;
                newf << oldFile.substr(offset, length);
                break;
            case 'x': // all commands are processed and end of file is reached, so return true
                return true;
            default: // if command is not recognized, return false
                return false;
        }
    }
    return false;
}