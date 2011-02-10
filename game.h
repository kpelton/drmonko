#ifndef GAME
#define GAME
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <time.h>
#include "GLobject.h"
#include "piece.h"
#include "board.h"
#include "timer.h"
#include "boardview.h"
#include "types.h"
#include "MenuWindow.h"

using namespace std;

static const int rows = 20;
static const int columns = 10;


class Game
{
public:
	virtual void renderScene(SDL_Event *event);
	Game(int width, int height);
	Game(int width,int height,float size,float center,
			float boardwidth,float start,float end, int argc,
			char **argv , const int *keys);
	Game();

	virtual ~Game();
private:
	boardview *bground;
	Piece *piece;
	Board *board;
	int width;
	int height;
	float size;
	float end;
	float start;
	bool checkWallCollision();
	bool movePossible();
	bool checkBoardCollision(const int row, const int col,const int rot) const;
	void drawNextPiece();
	void handleKeys(player_types::key key);
	void handleNoEvent();
	void handlePauseEvent(const string & selection);
	void newGame();
	bool animation;
	bool paused;
	MenuWindow *menu;
	const int *keys;
	SDLTimer * timer;
};
#endif
