// Player.cpp

#include "provided.h"
#include "support.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

const int SEARCH_DEPTH = 20; // set the limit of recursive depth for bestMove

// Used to store the two values that bestMove returns, as well as provide functions to access the values
class Result
{
public:
    Result(int rating, int moveCol) : m_rating(rating), m_moveCol(moveCol) {}
    int rating() const { return m_rating; } // return the rating for a move
    int moveCol() const { return m_moveCol; } // return the column on which a move is made
private:
    int m_rating;
    int m_moveCol;
};

class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
  private:
    Result bestMove(Scaffold& toRate, int N, int color, int computerColor, int currDepth, const vector<int>& cols);
    int rateScaffold(Scaffold& s, int N, int computerColor, int currDepth, bool& completed);
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    (void)N;
    if (s.numberEmpty() == 0) // if the scaffold is full, then can't make a move
        return -1;
    int colToMove = -1;
    cout << "choose a column to move on: ";
    cin >> colToMove;
    Scaffold checkMove = s; // create a copy of the scaffold to check the move on
    while (colToMove < 1 || colToMove > s.cols() || !checkMove.makeMove(colToMove, color))
    {
        cout << endl << "Please choose a valid column: "; // if the column chosen is invalid, reprompt for another column
        cin >> colToMove;
    }
    return colToMove;
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    (void)N;
    if (s.numberEmpty() == 0) // if the scaffold is full, then can't make a move
        return -1;
    int colToMove = -1; //
    Scaffold checkMove = s; // create a copy of the scaffold so it can be modified 
    for (int i = 1; i <= s.cols(); i++)
        if (checkMove.makeMove(i, color)) // if it's possible to move on a column, set the column to move on to that column
            colToMove = i;
    return colToMove; // if it's not possible to move on any column, the initial value -1 is returned
}

// bestMove finds the best move for the computer or the opponent depending on the color and computerColor parameters passed in
// It returns a Result that consists of the rating for the best move and the column on which the move is made
Result SmartPlayerImpl::bestMove(Scaffold& toRate, int N, int color, int computerColor, int currDepth, const vector<int>& cols)
{
    int otherColor = (color == RED) ? BLACK : RED; // intialize otherColor to the other player's color
    vector<Result> results; // create a vector to store the rating and column for each move
    for (size_t i = 0; i < cols.size(); i++)
    {
        if (toRate.makeMove(cols[i], color)) // check each move that can be made
        {
            bool completed;
            int rating = rateScaffold(toRate, N, computerColor, currDepth, completed); // rate the scaffold
            if (completed) // if the game is completed, insert the rating and column into results
                results.push_back(Result(rating, cols[i]));
            else if (currDepth+1 < SEARCH_DEPTH) // if recursive depth is less than the limit, call bestMove for the other player
                results.push_back(Result(bestMove(toRate, N, otherColor, computerColor, currDepth+1, cols).rating(), cols[i]));
            else // if recursive depth is at limit, assume any uncompleted game is a tie and insert rating and column into results
            {
                results.push_back(Result(0, cols[i]));
                toRate.undoMove();
                break;
            }
            toRate.undoMove(); // undo the move made
        }
    }
    size_t indexOfResult = 0;
    for (size_t i = 0; i < results.size(); i++)
    {
        if (color == computerColor) // if determining best move for computer, find the result with the most positive rating
        {
            if (results[i].rating() > results[indexOfResult].rating())
                indexOfResult = i;
        }
        else // if determining best move for the other player, find the result with the most negative rating
        {
            if (results[i].rating() < results[indexOfResult].rating())
                indexOfResult = i;
        }
    }
    return results[indexOfResult];
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (s.numberEmpty() == 0) // if the scaffold is full, then can't make a move
        return -1;
    Scaffold findMove = s; // make a copy of the scaffold so it can be modified
    vector<int> cols; // create a vector to store the order in which columns are to be checked by bestMove
    for (int i = 0; i <= findMove.cols()/2; i++) // fill the vector with columns numbers starting from the middle to the sides
    {
        cols.push_back(findMove.cols()/2+1-i);
        if (i > 0 && findMove.cols()/2+1+i <= findMove.cols())
            cols.push_back(findMove.cols()/2+1+i);
    }
    return bestMove(findMove, N, color, color, 0, cols).moveCol(); // returns the column that bestMove chooses
}

// Gives a rating for each scaffold that has a game that has been won or a tie game
// Returns a rating that depends on the current recursive depth and sets completed depending on whether a game is completed
int SmartPlayerImpl::rateScaffold(Scaffold& s, int N, int computerColor, int currDepth, bool& completed)
{
    int winner;
    if (isCompleted(s, N, winner)) // calls isCompleted to check if a game is completed
    {
        completed = true;
        if (winner == TIE_GAME)
            return 0;
        else if (winner == computerColor)
            return 1000 - currDepth; // returns a positive number minus recursive depth if winner is the computer
        else
            return -1000 + currDepth; // returns a negative number plus the recurve depth if other player is the winner
    }
    completed = false; // if the game is not completed
    return 0; // returns an arbitary value that isn't checked
}

//******************** Player derived class functions *************************

// These functions simply delegate to the Impl classes' functions.
// You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
