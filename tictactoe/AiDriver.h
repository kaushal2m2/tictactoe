//
//  AiDriver.h
//  tictactoe
//
//  Created by Kaushal Marimuthu on 5/22/23.
//

#ifndef AiDriver_h
#define AiDriver_h
#include "Node.hpp"

class AiDriver{
private:
    int t = 0, winAdd = 0, nAdd = 0;
    char get(int);
    double simRandom(Board *);
    void dfsSelect(Node * );
    void dfsDel(Node *);
public:
    int getMove(int, int, int, int, int, int, int, int, int);
};

#endif /* AiDriver_h */
