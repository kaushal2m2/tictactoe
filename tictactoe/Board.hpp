//
//  Board.hpp
//  tictactoe
//
//  Created by Kaushal Marimuthu on 5/21/23.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include <vector>
using namespace std;
class Board
{
public:
    char b[3][3];
    double wins = 0, n = 1;
    char turn = 'X';
    Board();
    Board(char[][3]);
    Board(const Board &);
    vector<Board *> genNext();
    bool equal(Board &);
    double EV(int);
    double done();
    bool horiz();
    bool vert();
    bool diag();
    double win();
};
#endif /* Board_hpp */
