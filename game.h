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
enum Status{
	INPROGRESS,
	WIN,
	LOSS,
};


class Game
{
public:
	virtual void renderScene(SDL_Event *event);
	Game(int width, int height);
	Game(int width,int height,float size,float center,
			float boardwidth,float start,float end, int argc,
			char **argv , const int *keys);
	Game();
	void setPaused(bool paused){this->paused = paused;};
	void newGame();
	Status getStatus(){return status;};
	int getVirusCount(){return board->getVirusCount();};
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
	bool movePossible(int add=1);
	bool checkBoardCollision(const int row, const int col,const int rot) const;
	void drawNextPiece();
	void handleKeys(player_types::key key);
	void handleNoEvent();

	bool animation;
	bool paused;
	const int *keys;
	SDLTimer * timer;
	Status status;
};
#endif
