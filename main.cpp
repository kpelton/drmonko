#include <iostream>
#include "sdlWindow.h"


int main (int argc, char **argv )
{
	sdlWindow window(argc,argv);
	SDL_WM_SetCaption("Dr Monko",NULL);
	window.renderLoop();
}
