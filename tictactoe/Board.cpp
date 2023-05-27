//
//  Board.cpp
//  tictactoe
//
//  Created by Kaushal Marimuthu on 5/21/23.
//

#include "Board.hpp"
Board::Board() {}
Board::Board(const Board &_b)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            b[i][j] = _b.b[i][j];
}
Board::Board(char _in [][3]){
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            b[i][j] = _in[i][j];
}
vector<Board *> Board::genNext()
{
    vector<Board*> nx;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (b[i][j] != 'X' && b[i][j] != 'O')
            {
                Board * diff = new Board(*this);
                diff->b[i][j] = turn;
                if (turn == 'X')
                    diff->turn = 'O';
                else
                    diff->turn = 'X';
                nx.push_back(diff);
                if (diff->done() == -1)
                    wins = -9999999; // if loss for AI
                if (diff->done() == 1)
                    wins = 9999999; // if win for AI
            }
    if (nx.size() == 0)
        return nx;
    double mx = nx[0]->wins, mn = nx[0]->wins;
    for (Board * nd : nx)
    {
        mx = max(mx, nd->wins);
        mn = min(mn, nd->wins);
    }
    if (mx < -999999)
        wins = -9999999; // if no states that dont lose
    if (mn > 999999)
        wins = 9999999; // if no states that dont win
    return nx;
}

bool Board::equal(Board &_b)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (b[i][j] != _b.b[i][j])
                return false;
    return true;
}

double Board::EV(int t)
{
    if (turn == 'O')
        return -1 * wins / n + sqrt(2 * log(t) / n);
    return wins / n + sqrt(2 * log(t) / n);
}

double Board::done()
{
    if (horiz() || vert() || diag())
        return win();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (b[i][j] != 'X' && b[i][j] != 'O')
                return -2;
    return 0;
}
bool Board::horiz()
{
    return (b[0][0] == b[0][1] && b[0][1] == b[0][2] && b[0][2] > 65) ||
           (b[1][0] == b[1][1] && b[1][1] == b[1][2] && b[1][2] > 65) ||
           (b[2][0] == b[2][1] && b[2][1] == b[2][2] && b[2][2] > 65);
}
bool Board::vert()
{
    return (b[0][0] == b[1][0] && b[1][0] == b[2][0] && b[2][0] > 65) ||
           (b[0][1] == b[1][1] && b[1][1] == b[2][1] && b[2][1] > 65) ||
           (b[0][2] == b[1][2] && b[1][2] == b[2][2] && b[2][2] > 65);
}
bool Board::diag()
{
    return (b[0][0] == b[1][1] && b[1][1] == b[2][2] && b[2][2] > 65) ||
           (b[2][0] == b[1][1] && b[1][1] == b[0][2] && b[0][2] > 65);
}
double Board::win()
{
    return turn == 'X' ? 1 : -1;
}
