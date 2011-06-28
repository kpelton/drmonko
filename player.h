#include "GLobject.h"
#include "mtrand.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:	
         virtual void renderScene(SDL_Event *event) = 0;
	 virtual ~Player(){};


protected:
	 MTRand RandEngine;
};
#endif
