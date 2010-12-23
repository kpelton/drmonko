#include "board.h"
#include <time.h>

using namespace piece_types;
Board::Board():GLobject()
{

}
Board::Board(const int trows,const int cols,const float size,
	     const float xstart, const float ystart,
	     const int width,const int height)
{
    this->nrows = trows;
    this->ncolumns=cols;
    this->size=size; 
    this->width = width; 
    this->xstart = xstart;
    this->ystart = ystart;
    this->height = height;
    clear();
    for (int i=10; i<rows; i++)
	for (int j=0; j<columns; j++)
	    if (rand()%5 == 4)
		board[i][j] = static_cast<ptype>(rand()%3);
    loadTextures();

}
bool Board::isFree(const int row, const int col)const
{
    if(board[row][col] != NOTHING)
	return false;
    return true;
}

void Board::clear()
{
    //clear all spaces
    for (int i=0; i<rows; i++){
	for(int j=0; j<columns; j++){
	    board[i][j] = NOTHING;
	}
    }
}
bool Board::loadTextures()
{
    GLobject::loadTextureFile("tiles/virusredsmall.bmp",&tiles[VIRUSRED]);
    GLobject::loadTextureFile("tiles/virusbluesmall.bmp",&tiles[VIRUSBLUE]);
    GLobject::loadTextureFile("tiles/virusyellowsmall.bmp",&tiles[VIRUSYELLOW]);
    return true;
}

bool Board::render()
{
     float currx = xstart;
     float curry = ystart;
     for (int i=0; i<rows; i++){
	 currx = xstart;
	for(int j=0; j<columns; j++){
	    if (board[i][j] != NOTHING)
		{ 
		    glBindTexture( GL_TEXTURE_2D,tiles[board[i][j]]);
		    glEnable(GL_TEXTURE_2D);
		    glEnable(GL_BLEND);
		    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		    glPushMatrix();
		    //set matrix mode to texture for rotations
		    glLoadIdentity();
		    glTranslatef(currx,curry,0.0);
	
		    glBegin(GL_QUADS); // Start drawing a quad primitive 
		    glTexCoord2i( 0, 0 );   glVertex2f(0, 0);
		    glTexCoord2i( 1, 0 );   glVertex2f(size, 0);
		    glTexCoord2i( 1, 1 );   glVertex2f(size, size);
		    glTexCoord2i( 0, 1);	glVertex2f(0,size);
		    glEnd(); 
		    glPopMatrix();
		    glColor4f(1.0,1.0,1.0,1.0);
		    
		}
	    currx+=size;
	}
	 curry+=size;
     }

    return true;
}
