#ifndef TWOPLAYER_H
#define TWOPLAYER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <time.h>
#include "GLobject.h"
#include "types.h"
#include "game.h"
#include "player.h"
#include <vector>
using namespace std;

class TwoPlayer: public Player
{
 public:
    virtual void renderScene(SDL_Event *event);
    TwoPlayer(int width,int height,float size,float center,
	      float boardwidth,float start,float end,
	      const int *keys,bool flip=false,const int players=2);

    virtual ~TwoPlayer();
	
 protected:
    virtual void handleKeys(player_types::key key);
    virtual void handlePauseEvent(const string & selection);
    virtual Status handleStatus(const Status status);
    Game *leftgame;
    Game *rightgame;
    void newGame(time_t seed);
 private:
    vector <Game *> games;
    int width;
    int height;
    float size;
    float end;
    float start;
    bool paused;
    MenuWindow *menu;
    const int *keys;
    SDLTimer * timer;	
    int leftcount;
    int rightcount;
	

};
#endif
