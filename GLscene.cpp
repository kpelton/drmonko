#include "GLscene.h"
#include "player.h"
#include "nplayer.h"
#include "types.h"
#include <iostream>

void GLscene::renderScene(SDL_Event *event)
{ 

	glLoadIdentity();


	glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    
	glPushMatrix();
	if(event && event->type == SDL_KEYDOWN){
		player1->handleKeyPress(event->key.keysym);
		if(player2)
			player2->handleKeyPress(event->key.keysym);	
	}
	else{
		player1->timerCb();
		if(player2)
			player2->timerCb();
	}
	player1->render();
	if(player2)
		player2->render();
 
	glPopMatrix();

	SDL_GL_SwapBuffers( );
    	
}

GLscene::GLscene()
{
	
}
GLscene::GLscene(const int width, const int height):width(width),height(height)
{
	player1 = new player(width,height,player_types::PLAYER1);
}

GLscene::GLscene(const int width, const int height,int argc,char **argv):width(width),height(height)
{
	player1 = NULL;
	player2 = NULL;
	if(argc >1)
	{
		if(strcmp(argv[1],"-s") == 0)
		{
			player1 = new nplayer(width,height,player_types::INTERNET_SERVER);
			cout << "Server" <<endl;
		}

		else if(strcmp(argv[1],"-c") == 0 )
		{
			player1 = new nplayer(width,height,player_types::INTERNET_CLIENT,argv[2]);
			cout << "Client connecting to"  <<argv[2] <<endl;

		}
	
		else if (strcmp(argv[1],"-2") == 0) {
		
			player1 = new player(width,height,player_types::INTERNET_SERVER);
			player2 = new player(width,height,player_types::PLAYER2);
		}
		else{
			player1 = new player(width,height,player_types::PLAYER1);
		}
	}else
	{
		player1 = new player(width,height,player_types::PLAYER1);
	}

}

GLscene::~GLscene()
{
	delete player1;
	if(player2)
		delete player2;
}
