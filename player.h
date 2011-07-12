//Copyright (c) 2011 Kyle Pelton
//See COPYING for license information
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
    MTRand randengine;
};
#endif
