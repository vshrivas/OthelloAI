#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
#include <vector>
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);
	int heuristic(Move* m, Side s);
	int heuristic_mm(Side s, Board *board);
	
	int minmaxhelper(vector<Board *> boards, int ply, int currply);
	Move * minmaxmain(Move * opponentMove, int msLeft);
	
	Move* minmaxmainfinal(Move* opponentMove, int msLeft);
	int minmaxhelperfinal(Board* board, int ply, int currply);
	
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
