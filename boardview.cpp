#include "boardview.h"
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <GL/glut.h>
#include "sdlWindow.h"
#define BLOCKSPACE 1

boardview::boardview()
{
	loadTextures();

}
bool boardview::loadTextures()
{
    GLobject::loadTextureFile("tiles/virusred.bmp",&tiles[1]);
    GLobject::loadTextureFile("tiles/tile1.bmp",&tiles[0]);
    GLobject::loadTextureFile("tiles/virusblue.bmp",&tiles[2]);
    GLobject::loadTextureFile("tiles/particle.bmp",&tiles[3]);
    font = GLobject::loadFont("fonts/Landmark.ttf",30);
    return true;
}
boardview::~boardview(){
	glDeleteTextures(3, tiles);
	TTF_CloseFont(font);

}
void boardview::drawBoardview()
{
    float hstart = height *.1;
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_TEXTURE_2D );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
		     GL_REPEAT);
    
    glColor4f(1.0,1.0,1.0,1.0);
    //draw board
    glBindTexture( GL_TEXTURE_2D, tiles[0] );
    glBegin(GL_QUADS); // Start drawing a quad primitive
    glTexCoord2i( 0, 0 );   glVertex2f(lstart, hstart);
    glTexCoord2i( 1, 0 );   glVertex2f(lend, hstart);
    glTexCoord2i( 1, 1 );   glVertex2f(lend, height);
    glTexCoord2i( 0, 1);	glVertex2f(lstart,height);
    glEnd();

//    glBindTexture( GL_TEXTURE_2D, tiles[1] );
//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_BLEND);
//
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//    glBegin(GL_QUADS); // Start drawing a quad primitive
//    glTexCoord2i( 0, 0 );   glVertex2f(0, height-128);
//    glTexCoord2i( 1, 0 );   glVertex2f(0+128, height-128);
//    glTexCoord2i( 1, 1 );   glVertex2f(0+128, height);
//    glTexCoord2i( 0, 1);	glVertex2f(0,height);
//
//    glEnd();
//    glBindTexture( GL_TEXTURE_2D, tiles[2] );
//    glBegin(GL_QUADS); // Start drawing a quad primitive
//    glTexCoord2i( 0, 0 );   glVertex2f(width-128, height-128);
//    glTexCoord2i( 1, 0 );   glVertex2f(width, height-128);
//    glTexCoord2i( 1, 1 );   glVertex2f(width, height);
//    glTexCoord2i( 0, 1);	glVertex2f(width-128,height);
//
//    glEnd();


    glDisable(GL_BLEND);
    glDisable( GL_TEXTURE_2D );
}

void boardview::drawText() const
{

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLobject::drawText(font, 0,255,0,(lstart+lend)/2.4, 0,"Dr. Monko");
	GLobject::drawText(font, 255,0,255,lend+25, height - (height*.9),"Next");

	GLobject::drawText(font, 255,0,255,lend+25, (height*.9) *.35,"Viruses");

	GLobject::drawText(font, 255,0,255,lend+25, (height*.9) *.6,"Score");
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);


}

void boardview::drawScore(const int score) const{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	char cscore[255];

	sprintf(cscore,"%i",score);
	GLobject::drawText(font, 0,191,255,lend+50, (height*.9)*.70,cscore);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void boardview::drawVirus(const int virus) const{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	char cvirus[255];

	sprintf(cvirus,"%i",virus);
	GLobject::drawText(font, 0,191,255,lend+50, (height*.9)*.47,cvirus);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

bool boardview::render()
{

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    drawBoardview();
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
    drawText();



    return true;
}
