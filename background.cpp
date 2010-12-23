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
    GLobject::loadTextureFile("tiles/virusred.bmp",&tiles[2]);
    GLobject::loadTextureFile("tiles/tile3.bmp",&tiles[1]);
    GLobject::loadTextureFile("tiles/virusblue.bmp",&tiles[3]);
    // GLobject::loadTextureFile("tiles/tile5.bmp",&tiles[4]);
    // GLobject::loadTextureFile("tiles/tile6.bmp",&tiles[5]);
    // GLobject::loadTextureFile("tiles/tile7.bmp",&tiles[6]);
    // GLobject::loadTextureFile("tiles/tile8.bmp",&tiles[7]);
    // GLobject::loadTextureFile("tiles/tile9.bmp",&tiles[8]);
    // GLobject::loadTextureFile("tiles/tile10.bmp",&tiles[8]);
    font = GLobject::loadFont("fonts/Landmark.ttf",42);
    return true;
}
void background::drawBackground()
{
    float hstart = height *.1;
    glEnable( GL_TEXTURE_2D );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
		     GL_REPEAT);
    
    glBindTexture( GL_TEXTURE_2D, tiles[1] );
    glBegin(GL_QUADS); // Start drawing a quad primitive 
    glTexCoord2i( 0, 0 );   glVertex2f(0, 0);
    glTexCoord2i( 4, 0 );   glVertex2f(width, 0);
    glTexCoord2i( 4, 4 );   glVertex2f(width, height);
    glTexCoord2i( 0, 4);	glVertex2f(0,height);
    glEnd(); 
 	
    glBindTexture( GL_TEXTURE_2D, tiles[0] );
    glBegin(GL_QUADS); // Start drawing a quad primitive 
    glTexCoord2i( 0, 0 );   glVertex2f(lstart, hstart);
    glTexCoord2i( 2, 0 );   glVertex2f(lend, hstart);
    glTexCoord2i( 2, 2 );   glVertex2f(lend, height);
    glTexCoord2i( 0, 2);	glVertex2f(lstart,height);

    glEnd(); 
    glBindTexture( GL_TEXTURE_2D, tiles[2] );
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS); // Start drawing a quad primitive 
    glTexCoord2i( 0, 0 );   glVertex2f(0, height-128);
    glTexCoord2i( 1, 0 );   glVertex2f(0+128, height-128);
    glTexCoord2i( 1, 1 );   glVertex2f(0+128, height);
    glTexCoord2i( 0, 1);	glVertex2f(0,height);

    glEnd(); 
    glBindTexture( GL_TEXTURE_2D, tiles[3] );
    glBegin(GL_QUADS); // Start drawing a quad primitive 
    glTexCoord2i( 0, 0 );   glVertex2f(width-128, height-128);
    glTexCoord2i( 1, 0 );   glVertex2f(width, height-128);
    glTexCoord2i( 1, 1 );   glVertex2f(width, height);
    glTexCoord2i( 0, 1);	glVertex2f(width-128,height);

    glEnd(); 


    glDisable(GL_BLEND);
    glDisable( GL_TEXTURE_2D );
}

bool background::render()
{

    
    drawBackground();
    float hstart = height *.1;
    //glColor3f(0.0f,1.0f,0.0f);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(lstart, hstart); // origin of the line
    glVertex2f(lstart, height); // ending point of the line
    glEnd( );

    glBegin(GL_LINES);
     
    glVertex2f(lend, hstart); // origin of the line
    glVertex2f(lend, height); // ending point of the line
    glEnd( );
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLobject::drawText(font, 0,255,0,(lstart+lend)/2.6, 0,"Dr. Monko");
    glDisable(GL_BLEND);
    return true;
}
