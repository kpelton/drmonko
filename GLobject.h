#ifndef GL_OBJECT
#define GL_OBJECT
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#ifdef _WIN32
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_ttf.h>
#else
#include "SDL.h"
#include "SDL_ttf.h"
#endif
#include <time.h>
#include <string>
#include <iostream>

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
    virtual ~GLobject(){};
    static TTF_Font* loadFont(const char *file, const int ptsize)
    {
	TTF_Font* tmpfont = NULL;
	tmpfont = TTF_OpenFont(file, ptsize);
	if (tmpfont == NULL)
	    cerr << "Unable to load font: " << TTF_GetError() <<endl;
	return tmpfont;
    }
    static void drawText(const TTF_Font *Font, const GLubyte& R, const GLubyte& G, const GLubyte& B, const double& X, const double& Y, const std::string& Text)
    {
	/*Create some variables.*/
	SDL_Color Color = {R, G, B};
	SDL_Surface *Message = TTF_RenderText_Blended(const_cast<TTF_Font*>(Font), Text.c_str(), Color);
	unsigned Texture = 0;
 
	/*Generate an OpenGL 2D texture from the SDL_Surface*.*/
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Message->w, Message->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, Message->pixels);
 
	/*Draw this texture on a quad with the given xyz coordinates.*/
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex2d(X, Y);
	glTexCoord2d(1, 0); glVertex2d(X+Message->w, Y);
	glTexCoord2d(1, 1); glVertex2d(X+Message->w, Y+Message->h);
	glTexCoord2d(0, 1); glVertex2d(X, Y+Message->h);
	glEnd();
 
	/*Clean up.*/
	glDeleteTextures(1, &Texture);
	SDL_FreeSurface(Message);
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
