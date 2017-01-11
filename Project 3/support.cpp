#include "support.h"
#include "provided.h"

bool isCompleted(const Scaffold& s, int N, int& winner)
{
    bool vertWon = false; // initialize a bool for each possible winning row direction
    bool horzWon = false;
    bool rightDiagWon = false;
    bool leftDiagWon = false;
    for (int i = 1; i <= s.levels(); i++)
    {
        for (int j = 1; j <= s.cols(); j++)
        {
            if (s.checkerAt(j, i) != VACANT)
            {
                if (i+N-1 <= s.levels()) // checks for N in a row vertically
                {
                    vertWon = true; // first assume there are N in a row vertically
                    for (int k = 1; k < N; k++)
                    {
                        if (s.checkerAt(j, i) != s.checkerAt(j, i+k))
                        {
                            vertWon = false; // if any position in the row is not the same as the first
                            break;
                        }
                    }
                    if (j >= N) // checks for N in a row diagonally left upwards
                    {
                        leftDiagWon = true;
                        for (int k = 1; k < N; k++)
                        {
                            if (s.checkerAt(j, i) != s.checkerAt(j-k, i+k))
                            {
                                leftDiagWon = false;
                                break;
                            }
                        }
                    }
                    if (j+N-1 <= s.cols()) // checks for N in a row diagonally right upwards
                    {
                        rightDiagWon = true;
                        for (int k = 1; k < N; k++)
                        {
                            if (s.checkerAt(j, i) != s.checkerAt(j+k, i+k))
                            {
                                rightDiagWon = false;
                                break;
                            }
                        }
                    }
                }
                if (j+N-1 <= s.cols()) // checks for N in a row horizontally
                {
                    horzWon = true;
                    for (int k = 1; k < N; k++)
                    {
                        if (s.checkerAt(j, i) != s.checkerAt(j+k, i))
                        {
                            horzWon = false;
                            break;
                        }
                    }
                }
                if (vertWon || horzWon || rightDiagWon || leftDiagWon) // if there are N in a row in any direction, the game is won
                {
                    winner = s.checkerAt(j, i);
                    return true;
                }
            }
        }
    }
    if (s.numberEmpty() == 0) // if there aren't N in a row in any direction and the scaffold is full, then game is a tie
    {
        winner = TIE_GAME;
        return true;
    }
    return false; // if the game isn't a tie then it's not completed
}