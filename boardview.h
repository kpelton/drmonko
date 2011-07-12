//Copyright (c) 2011 Kyle Pelton
//See COPYING for license information

#ifndef BOARDVIEW_H
#define BOARDVIEW_H
#include "GLobject.h"
#include <GL/gl.h>
#include <math.h>
#ifdef _WIN32
#include <SDL/SDL.h>
#else
#include "SDL.h"
#endif
#include <time.h>
#include "piece.h"
#include <string>
#include "particle.h"

using namespace std;

class boardview : public GLobject
{
	
 public:
    boardview();
    boardview(const int width, const int height, const float lstart, const float lend){this->width = width; this->height = height; this->lstart=lstart; this->lend=lend; loadTextures();};
    bool render();
    ~boardview();
    bool loadTextures();
    bool resize(){return false;};
    void setLevel(const Uint32 alevel){level=alevel;};
    void drawText() const;
    void drawScore(const int score) const;
    void drawVirus(const int virus) const;

 private:
    void drawBoardview();
    GLuint tiles[10];
    Uint32 level;
    int width;
    int height;
    float lstart;
    float lend;
    TTF_Font *font;
};


#endif
