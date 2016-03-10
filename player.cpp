#include "player.h"
#include <vector>
#include <iostream>
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
	//delete b;
}

Move* Player::minmax(Move* oppenentMove, int msLeft){
	// 
	vector <Move*> currmoves;
	vector <int> currmoves_scores;
	
	
	for(int x = 0; x < 8; x++){
		for(int y =0; y < 8; y++){
			Move* m = new Move(x,y);
			if(b.checkMove(m, s)){
				currmoves.push_back(m);
			}
		}
	}
	
	for(unsigned int i=0; i < currmoves.size(); i++){
		Board* board = b.copy();
		board->doMove(currmoves[i], s);
		int min = 1000000;
		Side other = (s == BLACK) ? WHITE : BLACK;
		for(int x = 0; x < 8; x++)
		{
			for(int y =0; y < 8; y++)
			{
				Move* oppm = new Move(x,y);
				if(board->checkMove(oppm, other))
				{
					int newscore = heuristic_mm(oppm, s, board);
							
					if (newscore < min)
					{
						min = newscore;
					} 
					else
					{
						delete oppm;
					}
				}
			}
		}
		currmoves_scores.push_back(min);
	}
	
	int max = -100000;
	Move *todo = NULL;
	for (unsigned int i = 0; i < currmoves_scores.size(); i++)
	{
		if (currmoves_scores[i] > max)
		{
			max = currmoves_scores[i];
			todo = currmoves[i];
		}
	}
	return todo;
	
}

int Player::heuristic_mm(Move* m, Side s, Board *board)
{
    /*int numwhite = b.countWhite();
    int numblack = b.countBlack();  */  
    
	Board *newb = board->copy();
    newb->doMove(m, s);
    
    int newnumwhite = newb->countWhite();
    int newnumblack = newb->countBlack();
    int score = 0;
    
    delete newb;
    
	if (s == BLACK)
    {
       // return newnumblack - numblack;
       score = newnumblack - newnumwhite;
    }
    else{
		//return newnumwhite - numwhite;
		score = newnumwhite - newnumblack;
	}
        if((m->getX() == 0 || m->getX() == 7) && (m->getY() == 0 || m->getY() == 7)){
		   score += 20;
	   }
	   else if((m->getX() == 0 || m->getX() == 1) && (m->getY() == 0 || m->getY() == 1)){
			score -= 20;
		}
		else if((m->getX() == 0 || m->getX() == 1) && (m->getY() == 6 || m->getY() == 7)){
			score -= 20;
		}
		else if((m->getX() == 6 || m->getX() == 7) && (m->getY() == 0 || m->getY() == 1)){
			score -= 20;
		}
		else if((m->getX() == 6 || m->getX() == 7) && (m->getY() == 6 || m->getY() == 7)){
			score -= 20;
		}
		return score; 
}

int Player::heuristic(Move* m, Side s)
{
    /*int numwhite = b.countWhite();
    int numblack = b.countBlack();  */  
    
	Board *newb = b.copy();
    newb->doMove(m, s);
    
    int newnumwhite = newb->countWhite();
    int newnumblack = newb->countBlack();
    int score = 0;
    
    delete newb;
    
	if (s == BLACK)
    {
       // return newnumblack - numblack;
       score = newnumblack - newnumwhite;
    }
    else{
		//return newnumwhite - numwhite;
		score = newnumwhite - newnumblack;
	}
        if((m->getX() == 0 || m->getX() == 7) && (m->getY() == 0 || m->getY() == 7)){
		   score += 20;
	   }
	   else if((m->getX() == 0 || m->getX() == 1) && (m->getY() == 0 || m->getY() == 1)){
			score -= 20;
		}
		else if((m->getX() == 0 || m->getX() == 1) && (m->getY() == 6 || m->getY() == 7)){
			score -= 20;
		}
		else if((m->getX() == 6 || m->getX() == 7) && (m->getY() == 0 || m->getY() == 1)){
			score -= 20;
		}
		else if((m->getX() == 6 || m->getX() == 7) && (m->getY() == 6 || m->getY() == 7)){
			score -= 20;
		}
		return score; 
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

	if (testingMinimax)
	{
		return minmax(opponentsMove, msLeft);
	}
	//cerr << "starting do move" << endl;
    int score = -1000000;
    Move* nextmove = NULL;

	//cerr << "next move created" << endl;
	//cerr << "default move set" << endl;


			Side other = (s == BLACK) ? WHITE : BLACK;
			// make opponent’s move
			if(opponentsMove != NULL){
				b.doMove(opponentsMove, other); 
			}
			
			//cerr << "made opponent's move" << endl;
			// check if board has move for player’s side
			if (b.hasMoves(s))
			{
				//cerr << "entering move calc" << endl;
				for (int x = 0; x < 8; x++)
				{
					for (int y = 0; y < 8; y++)
					{
						
							Move* currmove = new Move(x, y);
							if (b.checkMove(currmove, s))
							{
								int newscore = heuristic(currmove, s);
								//cerr << newscore << endl;
								
								if (newscore >= score)
								{
									//delete nextmove;
									nextmove = currmove;
									score = newscore;
								} 
								else{
									delete currmove;
								}
								
							}
					}
				}
			}
	b.doMove(nextmove, s);

	return nextmove;
	//return new Move(3,2);
}
