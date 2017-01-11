#ifndef SUPPORT_INCLUDED
#define SUPPORT_INCLUDED

#include <string>
using namespace std;

const int SEQ_LEN_1 = 8; // the length of sequences to be stored and checked
const int SEQ_LEN_2 = 16;
const int SEQ_LEN_3 = 24;
const int SEQ_LEN_4 = 36;
const double LOAD_FACTOR = 0.75; // load factor of the hash table

// A Sequence stores a sequence from the old file along with the offset where it was found
struct Sequence
{
    Sequence(string seq, size_t offset) : m_seq(seq), m_offset(offset) {}
    string m_seq;
    size_t m_offset;
};

// hashSize computes the number of buckets needed for the hash table depending
// on the number of characters in the file and the length of a sequence
inline int hashSize(size_t fileSize, int seqLen)
{
    return (fileSize-seqLen+1)/LOAD_FACTOR + 0.5; // add 0.5 so double to int truncating will always round up
}

bool getInt(istream& inf, int& n);

bool getCommand(istream& inf, char& cmd, int& length, int& offset);

// deltaCopy determines how long a match goes on when given a match
// and writes a copy instruction to the delta file
void deltaCopy(ostream& deltaf, const string& oldFile,
               const string& newFile, size_t& j, size_t offset, int seqLen);

#endif // SUPPORT_INCLUDED