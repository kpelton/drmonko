#include "GLscene.h"
#include "piece.h"
#include "types.h"
#include <iostream>

void GLscene::renderScene(SDL_Event *event)
{ 

	if(rightgame)
		rightgame->renderScene(event);

	if(leftgame)
		leftgame->renderScene(event);

}


GLscene::GLscene()
{
	
}
GLscene::GLscene(const int width, const int height):width(width),height(height)
{
    rightgame =  new Game(width,height);
}

GLscene::GLscene(const int width, const int height,int argc,char **argv):width(width),height(height)
{
	float size = ((height*.9)/rows*1.0);
	float center = width/2;
	float boardwidth = (columns*size);
	float start = center - (boardwidth/2);
	float end = start +(size *columns);

	leftgame = NULL;
	rightgame = NULL;



//	leftgame = new Game(width,height,size,center,boardwidth,start,end,
//			argc,argv,player_types::p1_keys);

	leftgame = new Game(width,height,size,center,boardwidth,0,boardwidth,
				argc,argv,player_types::p1_keys);

	rightgame = new Game(width,height,size,center,boardwidth,boardwidth,boardwidth*2,
				argc,argv,player_types::p2_keys);

}

GLscene::~GLscene()
{
	if(leftgame)
		delete leftgame;
	if(rightgame)
		delete rightgame;

}
