
#ifndef BOARD_H
#define BOARD_H
#include "GLobject.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#ifdef _WIN32
#include <SDL/SDL.h>
#else
#include "SDL.h"
#endif
#include <time.h>
#include "piece.h"
#include "background.h"
#include <string>
#include "types.h"
using namespace std;

class board 
{
	
public:
	board();
	board(const int width, const int height,const int lstart);
    	bool render();
    	~board();
    	bool loadTextures();
    	bool resize(){return false;};
	void handleKeyPress(player_types::tetris_key key);  	
	int  timerCb();
	const static int ROWWIDTH = 10; // blocks
	const static int COLUMNLENGTH = 23; //blocks
	Uint8 gameboard [ROWWIDTH] [COLUMNLENGTH];
	void addToBoard(Uint8 aboard[ROWWIDTH][COLUMNLENGTH]);
	piece &getNewPiece(){return newPiece;};
	void drawPiece();
	Uint32 getScore(){return score;};
	Uint32 getLevel(){return level;};
	Uint32 getLines(){return lines;};
	void addLines(const int num);
	void setScore(Uint32 score){this->score = score;};
	void setLines(Uint32 lines){this->lines = lines;};
	void setLevel(Uint32 level){this->level = level;
	    this->tbackground->setLevel(level);};
	void clearBoard();
	void drawString(string str,int y) const;
	
private:
	
	void drawBlocks();
	void updateRows();
	void newBlock();
	int checkLines();
	void rotatePiece();
	void jumpLevel();
	void doColor(int type);
	bool isDone();
	void drawNextPiece();
	void drawScore();
	void animateMoveY(float oldmove,float newmove);
	bool isPossible(int x, int y, int type, int rot);
	bool loadTextureFile(const char *location, GLuint *texture);
	piece newPiece;
	Uint32  start;
	void drawBlock(const float wstart, const float hstart, const float blocksize) const ;
	bool ready;
	Uint32 level;
	Uint32 score;
	Uint32 interval;
	Uint32 lines;
	Uint32 lineslevel;
	float blocksize;
	int width;
	int height;
	float lstart;
	GLuint blocktexture;
	background *tbackground;
	
	
};


#endif
