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
#include "particle.h"

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
	void addPiece(int num){board->addPiece(num);};
	virtual ~Game();
	void copyBoard(Game *other){board->copyBoard(*other->board);};
	int getRow(){return piece->getRow();};
	int getCol(){return piece->getCol();};
	int getRot(){return piece->getRotation();};
	Piece * getPiece(){return piece;};
	void setRow(const int row){piece->setRow(row);};
	void setCol(const int col){piece->setCol(col);};
	void setRot(const int rot){piece->setRotation(rot);};
	void addToBoard();
	void startGame();
	void copyPieces(Game *other){
	    piece->setListType1(other->piece->getListType1());
	    piece->setListType2(other->piece->getListType2());
	    piece->setCurr(other->piece->getCurr());
	};
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
	
	void addExplosion(int color);
	ParticleEngine pengine;
	void addTrail();
	bool animation;
	bool paused;
	const int *keys;
	SDLTimer * timer;
	Status status;
	void handleNoEvent();
};
#endif
