#ifndef BACKGROUND_H
#define BACKGROUND_H
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
#include <string>

using namespace std;

class background : public GLobject
{
	
public:
	background();
	background(const int width, const int height, const int lstart, const int lend){this->width = width; this->height = height; this->lstart=lstart; this->lend=lend; loadTextures();};
	bool render();
	~background(){};
	bool loadTextures();
	bool resize(){return false;};
	int  timerCb(){return 0;};
	void setLevel(const Uint32 alevel){level=alevel;};
	

private:
	void drawBackground();
	GLuint tiles[10];
	Uint32 level;
	int width;
	int height;
	int lstart;
	int lend;
	TTF_Font *font;
};


#endif
