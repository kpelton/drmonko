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
    viruses = 0;
    newGame();

    loadTextures();
    //pengine.startSnow();


}
void Board::copyBoard(Board &other){
    
    for (int i=0; i<rows; i++){
	for(int j=0; j<columns; j++){
	    board[i][j] = other.board[i][j];
	}
    }
}

void Board::addPiece(int num)
{
    int col = rand() %columns;
	for(int i=0; i<num; i++){
	    if (board[i][col].type == NOTHING){
		board[i][col].type = SETPILL;
		board[i][col].rot = NONE;
		board[i][col].col = static_cast<color>(rand() %3);
		}
	}

}
void Board::newGame()
{
	viruses = 0;
	clear();
	for (int i=10; i<rows; i++)
		for (int j=0; j<columns; j++)
			if (rand()%5 == 4){
				board[i][j].col = static_cast<color>(rand()%3);
				board[i][j].type = VIRUS;
				viruses++;
			}
}
void Board::checkVertical()
{
	color last=BLANK;
	int count = 0;
	int startrow=0;

	for (int j=0; j<columns; j++){
		count = 1;
		last = BLANK;
		for(int i=0; i<rows; i++){

			if (board[i][j].type != NOTHING){
				if (board[i][j].col != BLANK && board[i][j].col == last){
					if (count == 1)
						startrow = i;
					count++;
				}

				else{
					last = BLANK;
					count = 1;
				}
				last = board[i][j].col;

			}

			else{
				last = BLANK;
				count = 1;

			}
			if (count > 3){
				cout <<"Need to remove at col " <<j << " " << count <<endl;
				removeMatchVertical(startrow,j);
				count = 1;
				last = BLANK;
			}
		}
	}

}
void Board::checkHorizontal()
{
	color last=BLANK;
	int count = 0;
	int startcol = 0;
	for (int i=0; i<rows; i++){
		count = 1;
		last = BLANK;
		for(int j=0; j<columns; j++){

			if (board[i][j].type != NOTHING){
				if (board[i][j].col != BLANK && board[i][j].col == last){
					if (count == 1)
						startcol = j;
					count++;
				}
				else{
					last = BLANK;
					count = 1;
				}
				last = board[i][j].col;

			}
			else{
				last = BLANK;
				count = 1;

			}
			if (count > 3){
				cout <<"Need to remove at row " <<i << " " << count <<endl;
				removeMatchHorizontal(i,startcol);
				count = 1;
				last = BLANK
			;
			}
		}
	}
}

bool Board::moveDown()
{

	bool val = false;
	for (int i=rows-2; i>=0; i--){
			for(int j=0; j<columns; j++){
				if (board[i][j].type == SETPILL && board[i+1][j].type == NOTHING && board[i][j].rot == NONE){
					board[i+1][j].type = board[i][j].type;
					board[i+1][j].col = board[i][j].col;
					board[i+1][j].rot = board[i][j].rot;
					board[i][j].clear();
					val = true;
				}
				else if (board[i][j].type == SETPILL && board[i+1][j].type == NOTHING && board[i][j].rot != NONE){

					switch(board[i][j].rot){
					case LEFT:
						if (board[i][j+1].rot == RIGHT && board[i+1][j+1].type == NOTHING){
							board[i+1][j]  = board[i][j];
							board[i][j].clear();

							board[i+1][j+1] = board[i][j+1];
							board[i][j+1].clear();
							val = true;
						}
					case DOWN:
						if (board[i-1][j].rot == UP && board[i-1][j].type == SETPILL){
							board[i+1][j] = board[i][j];
							board[i][j].clear();

							board[i][j] =  board[i-1][j];
							board[i-1][j].clear();
							val = true;
						}

						break;
					default:
						break;

					}
				}

			}
		}
	return val;
}
bool Board::clearPieces()
{
	//returns true if done and ready to accept user input
	checkHorizontal();
    checkVertical();
    return  moveDown();
}

void Board::removeMatchVertical(const int startrow,const int col)
{
	//removes vertical  matches
	color start = board[startrow][col].col;
	float currx = xstart;
	float curry = ystart;
	int count = 0;
	cout << startrow <<endl;
	for(int i=startrow-1; i<rows; i++){

		if (board[i][col].type != NOTHING && board[i][col].col == start){
				count++;
				cout << i <<endl;

			if (board[i][col].type == VIRUS){
				viruses--;
				addExplosion(currx+(col*size),curry+(i*size),start);
			}

			if (board[i][col].type == SETPILL){
				changePillType(i,col);
				addExplosion(currx+(col*size),curry+(i*size),start);
			}

			board[i][col].type=NOTHING;
		}else{
			return;
		}
	}
}
void Board::addExplosion(const float x, const float y, const color col){
    

	switch(col){
		case RED:
			glColor4f(1.0,0.0,0.0,1.0);
			pengine.addExplosion(x,y,1,0,0);
			break;
		case YELLOW:
		        pengine.addExplosion(x,y,1,1,0);
		        break;
		case BLUE:
		        pengine.addExplosion(x,y,0,0,1);
			break;
		default:
			break;
    }
	

}
void Board::removeMatchHorizontal(const int row,const int startcol)
{
	//removes horizontal matches
	color start = board[row][startcol].col;
	float currx = xstart;
	float curry = ystart;
	int count = 0;
	cout << startcol <<endl;
	for(int j=startcol-1; j<columns; j++){

		if (board[row][j].type != NOTHING && board[row][j].col == start){
				count++;
			if (board[row][j].type == VIRUS){
				viruses--;
			       
				addExplosion(currx+(j*size),curry+(row*size),start);
			}
			if (board[row][j].type == SETPILL){
				changePillType(row,j);
				addExplosion(currx+(j*size),curry+(row*size),start);

			}
			board[row][j].type=NOTHING;

		}else{
			return;
		}
	}
}
void Board::changePillType(const int row, const int col)
{
	switch(board[row][col].rot)
	{
		case UP:
			board[row+1][col].rot = NONE;
			break;
		case DOWN:
			board[row-1][col].rot = NONE;
			break;
		case LEFT:
			board[row][col+1].rot = NONE;
			break;
		case RIGHT:
			board[row][col-1].rot = NONE;
			break;
		default:
			break;
	}
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
    GLobject::loadTextureFile("tiles/round.bmp",&tiles[BLANK]);
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
    color pcolor = board[row][col].col;
    
    
    glColor4f(1,1,1,1);
    glPushMatrix();
    //set matrix mode to texture for rotations
    glLoadIdentity();
    glTranslatef(x,y,0.0);
    //do correct rotation for texture allignment
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D,tiles[PILL]);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
			glScalef(1,-1,1);
			glRotatef(90,0,0,1);
			glTranslatef(-size/2,-size/2,0.0);
			break;
		case NONE:
			glBindTexture( GL_TEXTURE_2D,tiles[BLANK]);
			break;
		case UP:  //only rotate 2 piece second row
		       glTranslatef(size/2,size/2,0.0);
		       glScalef(-1,1,1);
		       glTranslatef(-size/2,-size/2,0.0);
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
    glDisable(GL_TEXTURE_2D);
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
					drawPill(currx,curry,i,j);
				}else{
					glBindTexture( GL_TEXTURE_2D,tiles[board[i][j].col]);
					glEnable(GL_TEXTURE_2D);
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glPushMatrix();
					//set matrix mode to texture for rotations
					glLoadIdentity();
					glTranslatef(currx+rand()%4,curry+rand()%4,0.0);
					
					glBegin(GL_QUADS); // Start drawing a quad primitive
					glTexCoord2i( 0, 0 );   glVertex2f(0, 0);
					glTexCoord2i( 1, 0 );   glVertex2f(size,0);
					glTexCoord2i( 1, 1 );   glVertex2f(size, size);
					glTexCoord2i( 0, 1);	glVertex2f(0,size);
					glEnd();
					glPopMatrix();
					glDisable(GL_BLEND);
					glDisable(GL_TEXTURE_2D);
				}
			}
			currx+=size;
		}
		curry+=size;
	}
	//render particles
	pengine.render();
    return true;
}
