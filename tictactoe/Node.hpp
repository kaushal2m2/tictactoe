//
//  Node.hpp
//  tictactoe
//
//  Created by Kaushal Marimuthu on 5/21/23.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include "Board.hpp"
class Node
{
public:
    Board * b;
    vector<Node *> succ;
    Node(Board *);
    void setS(vector<Board* >);
};
#endif /* Node_hpp */
