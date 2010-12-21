#ifndef GL_OBJECT
#define GL_OBJECT
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#ifdef _WIN32
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#else
#include "SDL.h"
#endif
#include <time.h>
#include <string>

#ifndef GL_BGR
#define GL_BGR GL_BGR_EXT
#endif
#ifndef GL_BGRA
#define GL_BGRA GL_BGRA_EXT
#endif

using namespace std;

class GLobject{

public:
	virtual bool render() = 0;
	virtual bool resize()=0;
	virtual bool loadTextures()=0;
	virtual int  timerCb()=0;
	virtual ~GLobject(){};
	virtual void handleKeyPress(SDL_keysym &keysym)=0;
	static void drawString(string str,void * font, int startx, int starty)
	{
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();

			glRasterPos2i(startx,starty);
			for (string::iterator i = str.begin(); i != str.end(); ++i)
			{
				char c = *i;
				glutBitmapCharacter(font, c);
			}
			glPopMatrix();
			glPushMatrix();


	}
	static bool loadTextureFile(const char *location, GLuint *texture)
	{

	SDL_Surface *surface;	// This surface will tell us the details of the image
	GLenum texture_format = 0;
	GLint  nOfColors = 0;
 
	if ( (surface = SDL_LoadBMP(location)) ) { 
 
		// Check that the image's width is a power of 2
		if ( (surface->w & (surface->w - 1)) != 0 ) {
			printf("warning: image.bmp's width is not a power of 2\n");
		}
	
		// Also check if the height is a power of 2
		if ( (surface->h & (surface->h - 1)) != 0 ) {
			printf("warning: image.bmp's height is not a power of 2\n");
		}
 
		// get the number of channels in the SDL surface
		nOfColors = surface->format->BytesPerPixel;
		if (nOfColors == 4)     // contains an alpha channel
		{
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGBA;
			else
				texture_format = GL_BGRA;
		} else if (nOfColors == 3)     // no alpha channel
		{
			if (surface->format->Rmask == 0x000000ff)
				texture_format = GL_RGB;
			else
				texture_format = GL_BGR;
		} else {
			printf("warning: the image is not truecolor..  this will probably break\n");
			// this error should not go unhandled
		}
        
		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, texture );
 
		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, *texture );
 
		// Set the texture's stretching properties
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
 
		// Edit the texture object's image data using the information SDL_Surface gives us
		glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
			      texture_format, GL_UNSIGNED_BYTE, surface->pixels );
	} 
	else {
		printf("SDL could not load image.bmp: %s\n", SDL_GetError());
		return false;
	}    
 
// Free the SDL_Surface only if it was successfully created
	if ( surface ) { 
		SDL_FreeSurface( surface );
	}

	return true;
}
private:
       

};
#endif
