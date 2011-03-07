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
		if(game)
			game->renderScene(event);
	}
}

void GLscene::setupGame(){
	float size = ((height*.9)/rows*1.0);
	float center = width/2;
	float boardwidth = (columns*size);
	float start = center - (boardwidth/2);
	float end = start +(size *columns);

	if (menu->getSelected() == "2 Player"){
	        game = new TwoPlayer(width,height,size,center,boardwidth,start,end,
				     0,NULL,NULL);
	    
	}else if (menu->getSelected() == "1 Player"){
		game = new SPlayer(width,height,size,center,boardwidth,start,end,
						0,NULL);
	}
	else if (menu->getSelected() == "2 Player Net Host"){
	    game = new NetPlayer(width,height,size,center,boardwidth,start,end,
				 0,NULL,player_types::INTERNET_SERVER);
	}
	else if (menu->getSelected() == "2 Player Net Connect"){
	    game = new NetPlayer(width,height,size,center,boardwidth,start,end,
				 0,NULL,player_types::INTERNET_CLIENT);
	}
	else if (menu->getSelected() == "Exit"){
		SDL_Quit();
	}

}


GLscene::GLscene(const int width, const int height,int argc,char **argv):width(width),height(height)
{

	font = GLobject::loadFont("fonts/Landmark.ttf",45);
	game = NULL;

	menu = new MenuWindow(width,height,"Select Game Type",font);
	menu->addOption("1 Player");
	menu->addOption("2 Player");
	menu->addOption("2 Player Net Host");
	menu->addOption("2 Player Net Connect");
	menu->addOption("Exit");

}

GLscene::~GLscene()
{
	TTF_CloseFont(font);
	if(game)
		delete game;
	if(menu)
		delete menu;
}
