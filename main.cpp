#include <iostream>
#include <GL/glut.h>
#include "sdlWindow.h"


int main (int argc, char **argv )
{
	sdlWindow window(argc,argv);
	window.renderLoop();
	

}
