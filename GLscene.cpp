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
	string host;
	
	if (menu->getSelected() == "2 Player"){
	    delete menu;
	    menu = new MenuWindow(width,height,"Select Game Type",font);
	    menu->addOption("Same Computer");
	    menu->addOption("Net Host");
	    menu->addOption("Net Connect");
	    menu->addOption("Exit");
	    return;
	    
	} else if(menu->getSelected() == "Same Computer"){
	
	    game = new TwoPlayer(width,height,size,center,boardwidth,start,end,
				 0,NULL,NULL);
	
	    
	}else if (menu->getSelected() == "1 Player"){
		game = new SPlayer(width,height,size,center,boardwidth,start,end,
						0,NULL);
	}
	else if (menu->getSelected() == "Net Host"){

	    game = new NetPlayer(width,height,size,center,boardwidth,start,end,
				 0,NULL,player_types::INTERNET_SERVER,"");
	}

	else if (menu->getSelected() == "Host"){
	    return;
	}
	else if (menu->getSelected() == "Connect"){
	host = menu->getInput("Host");
	game = new NetPlayer(width,height,size,center,boardwidth,start,end,
			     0,NULL,player_types::INTERNET_CLIENT,host);
	}

	else if (menu->getSelected() == "Net Connect"){
	    delete menu;
	    menu = new MenuWindow(width,height,"Net Connection",font);
	    menu->addInput("Host");
	    menu->addOption("Connect");
	    menu->addOption("Exit");
	    return;
	    
	  
	    
	}
	else if (menu->getSelected() == "Exit"){
	    exit(0);
	}
	delete menu;
	menu = NULL;

}


GLscene::GLscene(const int width, const int height,int argc,char **argv):width(width),height(height)
{

	font = GLobject::loadFont("fonts/Ubuntu-R.ttf",45);
	game = NULL;
	
	menu = new MenuWindow(width,height,"Select Game Type",font);
	menu->addOption("1 Player");
	menu->addOption("2 Player");
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
