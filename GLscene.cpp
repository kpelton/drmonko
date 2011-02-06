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

//	 glDisable(GL_TEXTURE_2D);
//	 glEnable( GL_BLEND );
//	 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	 glColor4f(0.0,0.0,0.0,0.8);
//
//	glBegin(GL_QUADS); // Start drawing a quad primitive
//	glVertex2f(0, 0);
//	glVertex2f(width, 0);
//	glVertex2f(width, height);
//	glVertex2f(0,height);
//	glEnd();
//
//
//	glColor4f(1.0,1.0,1.0,1.0);
//	glEnable(GL_TEXTURE_2D);
//	GLobject::drawText(font, 0,255,0,width/2, 200,"1 Player");
//	glColor4f(1.0,1.0,1.0,0.6);
//	GLobject::drawText(font, 0,255,0,width/2, 300, "2 Player");
//	glDisable(GL_TEXTURE_2D);
//	glDisable( GL_BLEND );


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
	font = GLobject::loadFont("fonts/Landmark.ttf",45);

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
