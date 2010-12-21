#include "player.h"

using namespace player_types;

player::player(const int width, const int height, const p_type type):height(height),width(width),type(type)
{
	if(type == INTERNET_CLIENT||
	   type == INTERNET_SERVER)
	{
		gameboard =  new board(width,height,1);
		keybinding = p1_keys;
	}
	else if(type == PLAYER1)
	{
		gameboard =  new board(width,height,width/3);
		keybinding = p1_keys;
	
	}
	
	else
	{
		gameboard =  new board(width,height,((height/20)*14) +1);
		keybinding = p2_keys;
	}
}
int  player::timerCb() 
{
	return gameboard->timerCb();
}

void player::handleKeyPress(SDL_keysym &keysym)
{
	tetris_key key=NONE;
	


	for(int i=0; i<6; i++)
	{
		if(keysym.sym == keybinding[i])
			key = static_cast<tetris_key>(i);
	}	
	
	if(key != NONE)
		gameboard->handleKeyPress(key);
}

bool player::render() 
{
  gameboard->render();
  gameboard->drawPiece();
	
	
	return true;
}


player::~player()
{
	delete gameboard;
}
