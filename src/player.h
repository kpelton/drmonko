//Copyright (c) 2011 Kyle Pelton
//See COPYING for license information
#include "GLobject.h"
#include "mtrand.h"
#include <SDL/SDL_mixer.h>
#ifndef PLAYER_H
#define PLAYER_H

class Player
{
 public:
  Player(){
    sound = Mix_LoadMUS("sound/main.wav");
    Mix_FadeInMusic(sound,-1,2000);
  };
    virtual void renderScene(SDL_Event *event) = 0;
    virtual ~Player(){};


 protected:
    MTRand randengine;
    Mix_Music *sound;
};
#endif
