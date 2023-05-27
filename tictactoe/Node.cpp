//
//  Node.cpp
//  tictactoe
//
//  Created by Kaushal Marimuthu on 5/21/23.
//

#include "Node.hpp"

Node::Node(Board *_b)
{
    b = _b;
}

void Node::setS(vector<Board * > v)
{
    for (Board *inb : v)
        succ.push_back(new Node(inb));
}
