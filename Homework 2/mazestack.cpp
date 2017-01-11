#include <iostream>
#include <stack>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    stack<Coord> mazeStack;
    mazeStack.push(Coord(sr, sc));
    maze[sr][sc] = '*';
    while (!mazeStack.empty())
    {
        Coord curr = mazeStack.top();
        mazeStack.pop();
        if (curr.r() == er && curr.c() == ec)
            return true;
        Coord north(curr.r()-1, curr.c());
        Coord east(curr.r(), curr.c()+1);
        Coord south(curr.r()+1, curr.c());
        Coord west(curr.r(), curr.c()-1);
        if (maze[north.r()][north.c()] == '.')
        {
            mazeStack.push(north);
            maze[north.r()][north.c()] = '*';
        }
        if (maze[east.r()][east.c()] == '.')
        {
            mazeStack.push(east);
            maze[east.r()][east.c()] = '*';
        }
        if (maze[south.r()][south.c()] == '.')
        {
            mazeStack.push(south);
            maze[south.r()][south.c()] = '*';
        }
        if (maze[west.r()][west.c()] == '.')
        {
            mazeStack.push(west);
            maze[west.r()][west.c()] = '*';
        }
    }
    return false;
}

/*
int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','.','.','.','.','.','.','.','.','X'},
        { 'X','X','.','X','.','X','X','X','X','X'},
        { 'X','.','.','X','.','X','.','.','.','X'},
        { 'X','.','.','X','.','.','.','X','.','X'},
        { 'X','X','X','X','.','X','X','X','.','X'},
        { 'X','.','X','.','.','.','.','X','X','X'},
        { 'X','.','.','X','X','.','X','X','.','X'},
        { 'X','.','.','.','X','.','.','.','.','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
    };
    
    if (pathExists(maze, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
*/