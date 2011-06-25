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
using namespace std;

class TwoPlayer: public Player
{
public:
	virtual void renderScene(SDL_Event *event);
	TwoPlayer(int width,int height,float size,float center,
			float boardwidth,float start,float end, int argc,
		  char **argv , const int *keys,bool flip=false);

	virtual ~TwoPlayer();

protected:
	virtual void handleKeys(player_types::key key);
	virtual void handlePauseEvent(const string & selection);
	Game *leftgame;
	Game *rightgame;
private:
	int width;
	int height;
	float size;
	float end;
	float start;
	bool paused;
	MenuWindow *menu;
	const int *keys;
	SDLTimer * timer;
	void handleStatus(const Status status);
	int leftcount;
	int rightcount;
	void newGame();

};
#endif
