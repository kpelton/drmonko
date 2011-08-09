//Copyright (c) 2011 Kyle Pelton
//See COPYING for license information
#include "sdlWindow.h"


int main (int argc, char **argv )
{
    sdlWindow window(argc,argv);
    SDL_WM_SetCaption("Dr Monko",NULL);
    window.renderLoop();
}
