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
	    if (rand()%5 == 4){
	    	board[i][j].col = static_cast<color>(rand()%3);
	    	board[i][j].type = VIRUS;
	    }

    loadTextures();


}
bool Board::isFree(const int row, const int col)const
{
    if(board[row][col].type != NOTHING)
    	return false;
    return true;
}

void Board::clear()
{
    //clear all spaces
    for (int i=0; i<rows; i++){
	for(int j=0; j<columns; j++){
		board[i][j].clear();
		}
    }
}
bool Board::loadTextures()
{
    GLobject::loadTextureFile("tiles/virusredsmall.bmp",&tiles[RED]);
    GLobject::loadTextureFile("tiles/virusbluesmall.bmp",&tiles[BLUE]);
    GLobject::loadTextureFile("tiles/virusyellowsmall.bmp",&tiles[YELLOW]);
    GLobject::loadTextureFile("tiles/pillhalf.bmp",&tiles[PILL]);
    return true;
}
void Board::addToBoard(const int rotation, const int row,const int col,const int type1, const int type2)
{
	int currow = row-1; //row is always starts 1 off
	int currcol = col;
	int type;

	for (int i = 0; i<3; i++){
		currcol = col;
		for (int j=1; j<3; j++){
			if (pieces[rotation][i][j]  != 0){

				type = (pieces[rotation][i][j] == 1) ? type1 : type2 ;

				board[currow][currcol].type = SETPILL;
				board[currow][currcol].col = static_cast<color> (type);

				if(i==0){
					board[currow][currcol].rot = UP;
				}
				else if(i ==1 && j==1 && (rotation == 1 || rotation == 3)){
					board[currow][currcol].rot = LEFT;
				}
				else if(rotation == 1 ||rotation ==3){
					board[currow][currcol].rot = RIGHT;
				}
				else{
					board[currow][currcol].rot = DOWN;
				}

			}
			currcol+=1;

		}
		currow+=1;
	}
}
void Board::drawPill(const float x,const float y, 
		     const int row,const int col) const 
{
    rotation rot =board[row][col].rot;
    ptype type = board[row][col].type;
    color pcolor = board[row][col].col;
    glPushMatrix();
    //set matrix mode to texture for rotations
    glLoadIdentity();
    glTranslatef(x,y,0.0);
    //do correct rotation for texture allignment
    glBindTexture( GL_TEXTURE_2D,tiles[PILL]);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    switch(rot){
		case LEFT: //only rotate 2 piece second row
			glTranslatef(size/2,size/2,0.0);
			glRotatef(270,0,0,1);
			glTranslatef(-size/2,-size/2,0.0);
			break;
		case DOWN:  //only rotate 2 piece second row
			glTranslatef(size/2,size/2,0.0);
			glRotatef(180,0,0,1);
			glTranslatef(-size/2,-size/2,0.0);
			break;
		case RIGHT: //only rotate 2 piece second row
			glTranslatef(size/2,size/2,0.0);
			glRotatef(90,0,0,1);
			glTranslatef(-size/2,-size/2,0.0);
			break;
		case NONE:
			glDisable(GL_TEXTURE_2D);
			break;

		default:
			break;
    }

    switch(pcolor){
		case RED:
			glColor4f(1.0,0.0,0.0,1.0);
			break;
		case YELLOW:
			glColor4f(1.0,1.0,0.0,1.0);
			break;
		case BLUE:
			glColor4f(0.0,0.0,1.0,1.0);
			break;
		default:
			break;
    }
    
    glMatrixMode(GL_MODELVIEW); 
    glBegin(GL_QUADS); // Start drawing a quad primitive 
    glTexCoord2i( 0, 0 );   glVertex2f(0, 0);
    glTexCoord2i( 1, 0 );   glVertex2f(size, 0);
    glTexCoord2i( 1, 1 );   glVertex2f(size, size);
    glTexCoord2i( 0, 1);	glVertex2f(0,size);
    glEnd(); 
    glPopMatrix();
    glColor4f(1.0,1.0,1.0,1.0);
    glDisable(GL_BLEND);
}

bool Board::render()
{
     float currx = xstart;
     float curry = ystart;
     for (int i=0; i<rows; i++){
	 currx = xstart;
	for(int j=0; j<columns; j++){
	    if (board[i][j].type != NOTHING)
		{ 
		    if (board[i][j].type != VIRUS){
			drawPill(currx,curry, 
				 i,j);
		    }else{
			glBindTexture( GL_TEXTURE_2D,tiles[board[i][j].col]);
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
			glDisable(GL_BLEND);
		    }
		}
	    currx+=size;
	}
	 curry+=size;
     }

    return true;
}
