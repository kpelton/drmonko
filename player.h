#ifndef PLAYER_H
#define PLAYER_H
#include "GLobject.h"
#include "board.h"
#include "types.h"

class player : public GLobject
{
 
public:

	player(){};
	virtual bool render( );
	virtual bool resize()  {return true;} ;
	virtual bool loadTextures() {return true;} ;
	virtual ~player();
	virtual int  timerCb() ;
        virtual void handleKeyPress(SDL_keysym &keysym);
	player(const int height, const int width, const player_types::p_type type);
	player_types::p_type   getType(){return type;} ; 
	board* getBoard() const {return gameboard;};
	int getHeight()const {return height;};

private:
	int height;
	int width;
	board *gameboard;
	player_types::p_type type;
	const int *keybinding;
	
         };
#endif
