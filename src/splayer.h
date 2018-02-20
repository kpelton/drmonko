//Copyright (c) 2011 Kyle Pelton
//See COPYING for license information
#ifndef SPLAYER
#define SPLAYER
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <time.h>
#include "GLobject.h"
#include "types.h"
#include "game.h"
#include "player.h"

using namespace std;

class SPlayer: public Player
{
 public:
    void renderScene(SDL_Event *event);
    SPlayer(int width,int height,float size,float center,
	    float boardwidth,float start,float end);

    virtual ~SPlayer();

    bool isDone();
 private:
    Game *game;
    int width;
    int height;
    float size;
    float end;
    float start;
    void handleKeys(player_types::key key);
    void handlePauseEvent(const string & selection);
    void newGame();
    bool paused;
    MenuWindow *menu;
    const int *keys;
    SDLTimer * timer;
    bool done;
};
#endif
