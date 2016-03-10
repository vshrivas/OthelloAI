#include "player.h"
#include <vector>
using namespace std;

/* CHANGE BY VAISHNAVI*/
/*
 * 
 * CHANGE BY MEERA
 * 
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */

Board b;
Side s;

Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    b = new Board;
    s = side;
    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

int heuristic(Move m, Side s)
{
    int numwhite = b.countWhite();
    int numblack = b.countBlack();    
    
	Board *newb = b.copy();
    (*newb).doMove(m, s);
    int newnumwhite = (*newb).countWhite();
    int newnumblack = (*newb).countBlack();
    
	if (s == BLACK)
    {
        return numblack - numnewblack;
    }

    else if (s == WHITE)
    {
        return numwhite - numnewwhite;
    }       
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
 
 
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 
    int score = 0;
    Move* nextmove;

    if(s == WHITE){
        nextmove->setX(4);
        nextmove->setY(3);
	}
	else{
		nextmove->setX(3);
		nextmove->setY(3);
	}

	// checking if opponent move is legal
	if (b.onBoard(opponentsMove.getX(), opponentsMove.getY()) && ! b.occupied(opponentsMove.getX(), opponentsMove.getY())
	{
			// find opponent’s side
			Side other = (s == BLACK) ? WHITE : BLACK;
			// make opponent’s move
			b.doMove(opponentsMove, other);
			
			// check if board has move for player’s side
			if (b.hasMoves(s))
			{
				for (int x = 0; x < 8; x++)
				{
					for (int y = 0; y < 8; y++)
					{
						if (!b.occupied(x, y))
						{
							Move* currmove = new Move(x, y);
							if (checkMove(currmove, s) == true)
							{
								int newscore = heuristic(currmove, s);
								if (newscore > score)
								{
									nextmove = currmove;
									score = newscore;
								}    
							}
						}
					}
				}
			}
	}

	return nextmove;
}
