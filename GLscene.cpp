#include "GLscene.h"
#include "piece.h"
#include <iostream>

void GLscene::renderScene(SDL_Event *event)
{ 
	game->renderScene(event);

}


GLscene::GLscene()
{
	
}
GLscene::GLscene(const int width, const int height):width(width),height(height)
{
    game =  new Game(width,height);
}

GLscene::GLscene(const int width, const int height,int argc,char **argv):width(width),height(height)
{
   game = new Game(width,height,argc,argv);

}

GLscene::~GLscene()
{
    delete game;

}
