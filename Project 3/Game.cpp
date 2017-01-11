// Game.cpp

#include "provided.h"
#include "support.h"
#include <iostream>
using namespace std;

class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    ~GameImpl();
    bool completed(int& winner) const; 
    bool takeTurn(); 
    void play();
    int checkerAt(int c, int r) const;
  private:
    Scaffold* m_scaffold; // pointer to the game's scaffold
    Player* m_red; // pointer to the red player
    Player* m_black; // pointer to the black player
    Player* m_currPlayer; // pointer to the player whose turn it is
    int m_nColumns;
    int m_nLevels;
    int m_n;
    int m_winner; // set to the winner if the game is won
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
: m_red(red), m_black(black), m_currPlayer(m_red), m_nColumns(nColumns), m_nLevels(nLevels), m_n(N), m_winner(-2)
{
    m_scaffold = new Scaffold(nColumns, nLevels); // dynamically allocate a new scaffold
}

GameImpl::~GameImpl()
{
    delete m_scaffold; // delete the scaffold when the game ends
}

bool GameImpl::completed(int& winner) const
{
    return isCompleted(*m_scaffold, m_n, winner); // calls helper function isCompleted
}

bool GameImpl::takeTurn()
{
    if (completed(m_winner)) // don't take a turn if the game is won
        return false;
    int currColor = (m_currPlayer == m_red) ? RED : BLACK; // initialize the current player's color
    cout << endl;
    m_scaffold->display();
    if (m_currPlayer->isInteractive()) // prompt a human player for a move
        cout << endl << m_currPlayer->name() << ", ";
    int columnToMove = m_currPlayer->chooseMove(*m_scaffold, m_n, currColor);
    m_scaffold->makeMove(columnToMove, currColor);
    cout << endl << m_currPlayer->name() << " has moved." << endl;
    m_currPlayer = (m_currPlayer == m_red) ? m_black : m_red; // set current player to the other player
    return true;
}

void GameImpl::play()
{
    while (takeTurn()) // keep taking turns until the game is won or tied
    {
        if (!m_red->isInteractive() && !m_black->isInteractive())
        {
            cout << "Press enter to continue.";
            cin.ignore(10000, '\n');
        }
    }
    cout << endl;
    m_scaffold->display();
    if (m_winner == RED)
        cout << endl << m_red->name() << " has won!" << endl;
    else if (m_winner == BLACK)
        cout << endl << m_black->name() << " has won!" << endl;
    else
        cout << endl << "Tie Game!" << endl;
}

int GameImpl::checkerAt(int c, int r) const
{
    return m_scaffold->checkerAt(c, r);
}

//******************** Game functions *******************************

// These functions simply delegate to GameImpl's functions.
// You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}
void Game::play()
{
    return m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
