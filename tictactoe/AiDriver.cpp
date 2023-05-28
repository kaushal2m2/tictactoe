//
//  AiDriver.cpp
//  tictactoe
//
//  Created by Kaushal Marimuthu on 5/21/23.
//

#include "AiDriver.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

char AiDriver::get(int a)
{
    if (a == 1)
        return 'X';
    if (a == 2)
        return 'O';
    return 0;
}

double AiDriver::simRandom(Board * board){
    srand((unsigned int)time(NULL));
    while(board->done() == -2){  //keeps doing random moves until game is over
        int e = 0;
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                if(board->b[i][j] != 'X' && board->b[i][j] != 'O')
                    e++;
        int rnd = (int)((int)(rand()) % e);   //chooses a random empty slot to fill
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                if(board->b[i][j] != 'X' && board->b[i][j] != 'O'){
                    if(rnd ==0){
                        board->b[i][j] = board->turn;
                        if(board->turn == 'X')
                            board->turn = 'O';
                        else
                            board->turn = 'X';
                    }
                    rnd--;
                }
    }
    return board->done();    //returns the utility value of the finished game
}

void AiDriver::dfsSelect(Node * curr){
    if(curr->succ.size() == 0){  //if this node is a leaf expand it
        curr->setS(curr->b->genNext());    //expansion
        nAdd = curr->succ.size() == 0 ? 1 : (int)(curr->succ.size());    //nAdd for backpropogation
        for(int i = 0; i < curr->succ.size(); i++){
            Board * nx = new Board(*(curr->succ[i]->b));
            curr->succ[i]->b->wins = simRandom(nx);   //simulation, and store values in winAdd for backpropogation
            winAdd += curr->succ[i]->b->wins;
            delete nx;
        }
        return;
    }
    int nx = 0;
    for(int i = 0; i < curr->succ.size(); i++){
        if(curr->succ[nx]->b->EV(t) < curr->succ[i]->b->EV(t))     //selection
            nx = i;
    }
    dfsSelect(curr->succ[nx]);
    curr->b->wins += winAdd;  //backpropogation
    curr->b->n += nAdd;
}

void AiDriver::dfsDel(Node * curr){
    for(int i = 0; i < curr->succ.size(); i++)
        dfsDel(curr->succ[i]);
    delete curr->b;
    delete curr;
}

int AiDriver::getMove(int s1, int s2, int s3, int s4, int s5, int s6, int s7, int s8, int s9)
{
    char b[3][3] = {{get(s1), get(s2), get(s3)},
                    {get(s4), get(s5), get(s6)},
                    {get(s7), get(s8), get(s9)}};
    
    int n = 100000;
    Board * r = new Board(b);
    r->turn = 'O';
    Node * curr = new Node(r);
    curr->setS(curr->b->genNext());
    t = 0;
    while(t < n){
        dfsSelect(curr); //use monte carlo search to make the tree
        nAdd = 0;
        winAdd = 0;
        t++;
    }
    int next = 0;
    for(int a = 0; a < curr->succ.size(); a++){
        if(curr->succ[next]->b->n < curr->succ[a]->b->n){      //pick the move which had most iterations
            next = a;
        }
        cout << curr->succ[a]->b->n << endl;
    }
    cout << endl << curr->succ[next]->b->n << endl << endl << endl;
    int ret = 0;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(r->b[i][j] != curr->succ[next]->b->b[i][j])
                ret = i * 3 + j;
        
    
    dfsDel(curr);
    return ret;
}
