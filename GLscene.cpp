#include "GLscene.h"
#include "background.h"
#include <iostream>

void GLscene::renderScene(SDL_Event *event)
{ 
	glLoadIdentity();

	glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
	glPushMatrix();

	bground->render();
	glPopMatrix();
}

GLscene::GLscene()
{
	
}
GLscene::GLscene(const int width, const int height):width(width),height(height)
{
    bground = new background(width,height,width*.25,width*.25);
}

GLscene::GLscene(const int width, const int height,int argc,char **argv):width(width),height(height)
{
    bground = new background(width,height,width*.25,width*.75);

}

GLscene::~GLscene()
{

}
