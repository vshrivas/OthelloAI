#include "player.h"
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
    testingMinimax = true;
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
Move* Player::minmaxmainfinal(Move* opponentMove, int msLeft){
	vector <Move*> moves;
	vector <int> scores;
	for(int x=0; x < 8; x++){
		for(int y=0; y < 8; y++){
			Move* m = new Move(x,y);
			if(b.checkMove(m,s)){
				Board* board = b.copy();
				board->doMove(m, s);
				moves.push_back(m);
				int score = minmaxhelperfinal(board, 2, 0);
				scores.push_back(score);
			}
		}
	}
	int maxscore = -1000000;
	Move* todo = NULL;
	for(unsigned int i = 0; i < scores.size(); i++){
		if(scores[i] > maxscore){
			maxscore = scores[i];
			todo = moves[i];
		}
	} 
	if (todo != NULL)
	{
		b.doMove(todo, s);
	}
		
	cerr << todo->getX() << todo->getY() << endl;
	return todo;
}

int Player::minmaxhelperfinal(Board* board, int ply, int currply){
	if(currply == ply){
		int score = heuristic_mm(s, board);
		return score;
	}
	else{
		vector <int> scores;
		for(int x=0; x < 8; x++){
			for(int y=0; y < 8; y++){
				Move* m = new Move(x,y);
				if(board->checkMove(m,s)){
					Board* newboard = board->copy();
					newboard->doMove(m, s);
					//moves.push_back(m);
					int score = minmaxhelperfinal(newboard, ply, currply + 1);
					scores.push_back(score);
				}
			}
		}
		if(currply == ply - 1){
			int min = 1000000;
			for(unsigned int i=0; i < scores.size(); i++){
				if(scores[i] < min){
					min = scores[i];
				}
			}
			return min;
		}
		else{
			int max = -100000;
			for(unsigned int i=0; i < scores.size(); i++){
				if(scores[i] > max){
					max = scores[i];
				}
			}
			return max;
		}
	}
}

Move* Player::minmaxmain(Move* opponentMove, int msLeft){
	vector <Move*> moves;
	vector <int> scores;
	//cerr << "main function " << endl;
	// iterate through every square on the board
	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			//cerr << "first for loop" << endl;
			// create a new move
			Move* m = new Move(x,y);
			// if the move is valid
			if(b.checkMove(m, s)){
				// copy the board
				vector<Board*> boards;
				Board* board = b.copy();
				//cerr << "check move start" << endl;
				// make the move on the board
				board->doMove(m, s);
				boards.push_back(board);
				moves.push_back(m);
				scores.push_back(minmaxhelper(boards, 2, 0));
				//cerr << scores[scores.size()-1] << endl;
				//cerr << "check move end" << endl;
			}
			else
			{
				//delete m;
			}
		}
	}

		int max = -100000;
		Move *todo = NULL;
		for (unsigned int i = 0; i < scores.size(); i++)
		{
			//cerr << "check max " << endl;
			if (scores[i] > max)
			{
				max = scores[i];
				todo = moves[i];
			}
		}
		if (todo != NULL)
		{
			b.doMove(todo, s);
		}
		
		cerr << todo->getX() << todo->getY() << endl;
		return todo;
	
}

int Player::minmaxhelper(vector<Board*> boards, int ply, int currply){
	// base case at ply
	if(currply == ply){
		int min = 10000000;
		//cerr << "base case start " << endl;
		for (unsigned int i = 0; i < boards.size(); i++)
		{
			//cerr << "for loop in base case " << endl;
			int score = heuristic_mm(s, boards[i]);
			//cerr << "heuristic calculation is successfull" << endl;
			if (score < min)
			{
				min = score;
				//cerr << "finding score " << endl;
			}
		}
		//cerr << "found a min " << endl;
		return min;
	}
	else{
		//cerr << "in else case " << endl;
		vector <Board*> oppboards;
		vector <Board*> ourboards;
		for(unsigned int i=0; i < boards.size(); i++){
			//cerr << "there are boards!!" << endl;
			Side other = (s == BLACK) ? WHITE : BLACK;
			for(int x = 0; x < 8; x++)
			{
				for(int y =0; y < 8; y++)
				{
					//cerr << "for loops in helper" << endl;
					Move* oppm = new Move(x,y); // moves that opponent makes
					if(boards[i]->checkMove(oppm, other))
					{
						//cerr << "check move in helper" << endl;
						Board* oppboard = boards[i]->copy();
						oppboard->doMove(oppm, other);
						oppboards.push_back(oppboard);
						//cerr << "found move in helper" << endl;				
					}
					else
					{
						//delete oppm;
					}
				}
			}
		}
		
		
		for(unsigned int i=0; i < oppboards.size(); i++){
			for(int x = 0; x < 8; x++)
			{
				for(int y =0; y < 8; y++)
				{
					//cerr << "for loops to find our moves "<< endl;
					Move* ourmove = new Move(x,y); // moves that we make
					if(oppboards[i]->checkMove(ourmove, s))
					{
						//cerr << "found move for us " << endl;
						Board* ourboard = oppboards[i]->copy();
						ourboard->doMove(ourmove, s);
						ourboards.push_back(ourboard);		
						//cerr << "pushed move for us" << endl;		
					}
					else
					{
						//delete ourmove;
					}
				}
			}
		}		
		return minmaxhelper(ourboards, ply, currply+1);
		
		
	}
	
}

int Player::heuristic_mm(Side s, Board *board)
{
    /*int numwhite = b.countWhite();
    int numblack = b.countBlack();  */  
    
    int newnumwhite = board->countWhite();
    int newnumblack = board->countBlack();
    int score = 0;

	if (s == BLACK)
    {
       // return newnumblack - numblack;
       score = newnumblack - newnumwhite;
    }
    else
    {
		//return newnumwhite - numwhite;
		score = newnumwhite - newnumblack;
	}
    
    vector <Move*> corners;
    //cerr << "made corners " << endl;
    vector <Move*> nearcorners;
    //cerr << "made nearcorners " << endl;
    
    corners.push_back(new Move(0, 0));
    corners.push_back(new Move(0, 7));
    corners.push_back(new Move(7, 0));
    corners.push_back(new Move(7, 7));
    
    //cerr << "put values in corners" << endl;
    
    nearcorners.push_back(new Move(1, 0));
    nearcorners.push_back(new Move(0, 1));
    nearcorners.push_back(new Move(1, 1));
    
    nearcorners.push_back(new Move(6, 7));
    nearcorners.push_back(new Move(7, 6));
    nearcorners.push_back(new Move(6, 6));
   
    nearcorners.push_back(new Move(0, 6));
    nearcorners.push_back(new Move(1, 7));
    nearcorners.push_back(new Move(1, 6));
    
    nearcorners.push_back(new Move(6, 0));
    nearcorners.push_back(new Move(6, 1));
    nearcorners.push_back(new Move(7, 1));
    
    //cerr << "put values in newcorners" << endl;
    
    //cerr << "corner size " << corners.size() << endl;
    //cerr << "near corner size " << nearcorners.size() << endl;
    
    for (unsigned int i = 0; i < corners.size(); i++)
    {
		//cerr << "in corners for loop" << endl;
		//cerr << "corner x " << corners[i]->getX() << "corner y " << corners[i]->getY() << endl;
		//cerr << "boolean get " << board->get(s, corners[i]->getX(), corners[i]->getY()) << endl;
		if (board->get(s, corners[i]->getX(), corners[i]->getY()))
		{
			//cerr << "corner piece found" << endl;
			score += 20;
		}
	}
	//cerr << "done with corners " << endl;
	for (unsigned int i = 0; i < nearcorners.size(); i++)
	{
		//cerr << "in near corners for loop" << endl;
		//cerr << "nearcorners x " << nearcorners[i]->getX() << "nearcorner y " << nearcorners[i]->getY() << endl;
		//cerr << "boolean get " << board->get(s, nearcorners[i]->getX(), nearcorners[i]->getY()) << endl;
		
		//cerr << "boolean get 6 " << board->get(s, 6, 6) << endl;
		if (board->get(s, nearcorners[i]->getX(), nearcorners[i]->getY()))
		{
			//cerr << "near corner piece found" << endl;
			score -= 20;
		}
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
	
	if (testingMinimax)
	{
		return minmaxmainfinal(opponentsMove, msLeft);
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
