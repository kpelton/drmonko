#include "GLscene.h"
#include "piece.h"
#include "types.h"
#include <iostream>

void GLscene::renderScene(SDL_Event *event)
{ 
	glLoadIdentity();
	glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if (menu){
		if (!menu->handleEvent(event))
		{
			menu->render();
		}else{
			setupGame();
			delete menu;
			menu = NULL;
		}
	}else{
		if(leftgame)
			leftgame->renderScene(event);
		if(rightgame)
			rightgame->renderScene(event);
	}
}


GLscene::GLscene()
{
	
}

void GLscene::setupGame(){
	float size = ((height*.9)/rows*1.0);
	float center = width/2;
	float boardwidth = (columns*size);
	float start = center - (boardwidth/2);
	float end = start +(size *columns);

	if (menu->getSelected() == "2 Player"){
		rightgame = new Game(width,height,size,center,boardwidth+25,25,boardwidth+25,
				0,NULL,player_types::p2_keys);

		start = (boardwidth+25)+150;
		end = start +(size *columns);
		leftgame = new Game(width,height,size,center,boardwidth,start,end,
				0,NULL,player_types::p1_keys);
	}else if (menu->getSelected() == "1 Player"){
		leftgame = new Game(width,height,size,center,boardwidth,start,end,
				0,NULL,player_types::p1_keys);
	}
	else if (menu->getSelected() == "Exit"){
		SDL_Quit();
	}

}
GLscene::GLscene(const int width, const int height):width(width),height(height)
{
    rightgame =  new Game(width,height);
}

GLscene::GLscene(const int width, const int height,int argc,char **argv):width(width),height(height)
{

	font = GLobject::loadFont("fonts/Landmark.ttf",45);
	leftgame = NULL;
	rightgame = NULL;

	menu = new MenuWindow(width,height,"Select Game Type",font);
	menu->addOption("1 Player");
	menu->addOption("2 Player");
	menu->addOption("Exit");

}

GLscene::~GLscene()
{
	TTF_CloseFont(font);
	if(leftgame)
		delete leftgame;
	if(rightgame)
		delete rightgame;
	if(menu)
		delete menu;
}
