#include "GLscene.h"
#include "piece.h"
#include "types.h"
#include <iostream>

void GLscene::renderScene(SDL_Event *event)
{ 
	glLoadIdentity();
	glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if(leftgame)
		leftgame->renderScene(event);
	if(rightgame)
	rightgame->renderScene(event);

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






	if (argc >1 && (strcmp(argv[1],"-2") == 0)){
	rightgame = new Game(width/2,height,size,center,boardwidth+25,25,boardwidth+25,
				argc,argv,player_types::p2_keys);

	start = (boardwidth+25)+150;
	end = start +(size *columns);
	leftgame = new Game(width/2,height,size,center,boardwidth,start,end,
				argc,argv,player_types::p1_keys);
	}else{
			leftgame = new Game(width,height,size,center,boardwidth,start,end,
					argc,argv,player_types::p1_keys);
	}

}

GLscene::~GLscene()
{
	if(leftgame)
		delete leftgame;
	if(rightgame)
		delete rightgame;

}
