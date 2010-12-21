#include "background.h"
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <GL/glut.h>
#include "sdlWindow.h"
#define BLOCKSPACE 1

background::background()
{
	loadTextures();

}
bool background::loadTextures()
{
	GLobject::loadTextureFile("tiles/tile1.bmp",&tiles[0]);
	GLobject::loadTextureFile("tiles/tile2.bmp",&tiles[1]);
	GLobject::loadTextureFile("tiles/tile3.bmp",&tiles[2]);
	GLobject::loadTextureFile("tiles/tile4.bmp",&tiles[3]);
	GLobject::loadTextureFile("tiles/tile5.bmp",&tiles[4]);
	GLobject::loadTextureFile("tiles/tile6.bmp",&tiles[5]);
	GLobject::loadTextureFile("tiles/tile7.bmp",&tiles[6]);
	GLobject::loadTextureFile("tiles/tile8.bmp",&tiles[7]);
	GLobject::loadTextureFile("tiles/tile9.bmp",&tiles[8]);
	GLobject::loadTextureFile("tiles/tile10.bmp",&tiles[8]);
	return true;
}
void background::drawBackground()
{

	glEnable( GL_TEXTURE_2D );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
			GL_REPEAT);
	glBindTexture( GL_TEXTURE_2D, tiles[level-1] );

	glBegin(GL_QUADS); // Start drawing a quad primitive 
	glTexCoord2i( 0, 0 );   glVertex2f(lstart, 0);
	glTexCoord2i( 2, 0 );   glVertex2f(lend, 0);
	glTexCoord2i( 2, 2 );   glVertex2f(lend, height);
	glTexCoord2i( 0, 2);	glVertex2f(lstart,height);
	glEnd();  	
	glDisable( GL_TEXTURE_2D );
}

bool background::render()
{

	glColor3f(1.0f,1.0f,1.0f);
	drawBackground();

	glBegin(GL_LINES);
	glVertex2f(lstart, 0.0f); // origin of the line
	glVertex2f(lstart, height); // ending point of the line
	glEnd( );

	glBegin(GL_LINES);
	glVertex2f(lend, 0.0f); // origin of the line
	glVertex2f(lend, height); // ending point of the line
	glEnd( );

	return true;
}
