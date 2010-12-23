#include "piece.h"
#include <stdlib.h>
#include <time.h>

using namespace piece_types;
Piece::Piece():GLobject()
{
    loadTextures();
    firstPiece(7);
}
bool Piece::loadTextures()
{
    GLobject::loadTextureFile("tiles/pillhalf.bmp",&texture);
    return true;
}
void Piece::rotLeft()
{
    if (rotation <3)
	rotation++;
    else
	rotation = 0;
}
float Piece::getMaxX()const
{
    float startx = x+size;
    for (int i=0;i<3; i++){
	    for (int j=2; j>=0; j--){ //row
		float  currx=startx +(i*size);
		if (pieces[rotation][i][j] != 0)
		    return currx;
	    }
	}
    return 0;
}

void Piece::rotRight()
{
     if (rotation >0)
	 rotation--;
     else
	 rotation=3;
}
bool Piece::render()
{
    float currx = x;
    float curry = y;
    float startx = x-size;

    currx -=size; //start in upper left corner
    curry -=size; //start first row
    glBindTexture( GL_TEXTURE_2D,texture);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (int i=0; i<3; i++){ //row
	currx = startx-size; //start far left
	for(int j=0; j<3; j++){ //column
	    if(j==0)
		currx+=size;
	    if (pieces[rotation][i][j] != 0){
		glPushMatrix();
		//set matrix mode to texture for rotations
		glLoadIdentity();
    		glTranslatef(currx,curry,0.0);
		//do correct rotation for texture allignment
		
		if(rotation == 0 || rotation == 2){
		    glTranslatef(size/2,size/2,0.0);
		    if(i==1) //only rotate 2 piece second row	
			glRotatef(180,0,0,1);
		    glTranslatef(-size/2,-size/2,0.0);
		}

		else if (rotation == 1 || rotation == 3){ //only rotate 2 piece second row
		    glTranslatef(size/2,size/2,0.0);
		    if (j==1)
			glRotatef(270,0,0,1);
		    else if (j==2)
			glRotatef(90,0,0,1);

		    glTranslatef(-size/2,-size/2,0.0);
		}
		if(pieces[rotation][i][j] == 1)
		    doColor(type1);
		else
		    doColor(type2);

		glMatrixMode(GL_MODELVIEW); 
	        glBegin(GL_QUADS); // Start drawing a quad primitive 
		glTexCoord2i( 0, 0 );   glVertex2f(0, 0);
		glTexCoord2i( 1, 0 );   glVertex2f(size, 0);
		glTexCoord2i( 1, 1 );   glVertex2f(size, size);
		glTexCoord2i( 0, 1);	glVertex2f(0,size);
		glEnd(); 
		glPopMatrix();
		}
		currx+=size;
		glColor4f(1.0,1.0,1.0,1.0);
	}
	curry+=size;
    }

    return true;
}

void Piece::doColor(const int ctype) const
{
    switch(ctype){
    case RED:
	glColor4f(1.0,0.0,0.0,1.0);
	break;
    case YELLOW:
	glColor4f(1.0,1.0,0.0,1.0);
	break;
    case BLUE:
	glColor4f(0.0,0.0,1.0,1.0);
	break;
    }
	
}
void Piece::firstPiece(const int middle)
{
    srand(time(NULL));
    type1 = rand()%3;
    type2 = rand()%3;
    rotation = 1;
    nextPiece();
}

void Piece::nextPiece()
{
	ntype1 = rand()%3;
	ntype2 = rand()%3;
	nrotation = 1;
}
void Piece::newPiece(const int x, const int y,const int middle)
{
    //sets the current piece from the nextpiece
    type1 = ntype1;
    type2 = ntype2;
    this->x =  x;
    this->y =  y;
    rotation = nrotation;
    //Get a new Piece
    nextPiece();
}

int Piece::getBlockType(int x, int y)
{
    //return pieces[type][rotation][x][y];
    return 0;
}



