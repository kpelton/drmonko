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
	void renderScene(SDL_Event *event);
	TwoPlayer(int width,int height,float size,float center,
			float boardwidth,float start,float end, int argc,
			char **argv , const int *keys);

	virtual ~TwoPlayer();
private:
	Game *leftgame;
	Game *rightgame;
	int width;
	int height;
	float size;
	float end;
	float start;
	void handleKeys(player_types::key key);
	void handlePauseEvent(const string & selection);
	bool paused;
	MenuWindow *menu;
	const int *keys;
	SDLTimer * timer;
	void handleStatus(const Status status);
};
#endif
