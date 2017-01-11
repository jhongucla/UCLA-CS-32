#ifndef SUPPORT_INCLUDED
#define SUPPORT_INCLUDED

#include "provided.h"

// Checks for N in a row on Scaffold s
// If a player has won or the game is tied, winner is set to RED, BLACK, or TIE_GAME and returns true
// If the game is not completed, winner is unchanged and returns false
bool isCompleted(const Scaffold& s, int N, int& winner);

#endif // SUPPORT_INCLUDED
