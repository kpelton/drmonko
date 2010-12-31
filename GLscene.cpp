#include "GLscene.h"
#include "background.h"
#include "piece.h"
#include <iostream>

void GLscene::renderScene(SDL_Event *event)
{ 
	glLoadIdentity();
	int row;
	int col;
	int rot = piece->getRotation();
	glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    	if(event && event->type == SDL_KEYDOWN){
	    switch(event->key.keysym.sym){

	    case SDLK_LEFT:
		//only move it if doesn't go out of the board
		row =piece->getRow();
		col = piece->getCol()-1;
		if(col >=0 && checkBoardCollision(row,col,rot)){
		    piece->setCoords(piece->getX()-size,piece->getY());
		    piece->setCol(piece->getCol()-1);
		}
		break;
	    case SDLK_RIGHT:
		row =piece->getRow();
		col = piece->getCol()+1;
		//only move it if doesn't go out of the board
		if(piece->getMaxX()+size <= end  && checkBoardCollision(row,col,rot) ){
		    piece->setCoords(piece->getX()+size,piece->getY());
		    piece->setCol(piece->getCol()+1);
		}
		break;
	    case SDLK_UP:
		row =piece->getRow();
		col = piece->getCol();
		piece->rotLeft();
		rot = piece->getRotation();
		
		//if the move is not valid put it back to the way it was
		if (!checkBoardCollision(row,col,rot) || piece->getMaxX() > end)
		    piece->rotRight();
		break;
	    case SDLK_DOWN:
	    	if (movePossible()){
	    		piece->setCoords(piece->getX(),piece->getY()+size);
	    		piece->setRow(piece->getRow()+1);
	    	}
		break;
	    case SDLK_ESCAPE:
		SDL_Quit();
	    default:
		break;
	    }
	}
    row =piece->getRow();
    col = piece->getCol();
    rot = piece->getRotation();
    if(event == NULL){
    	if (timer->isDone()){
    			if (movePossible()){
    			piece->setCoords(piece->getX(),piece->getY()+size);
    			piece->setRow(piece->getRow()+1);

    		}else{
    				board->addToBoard(rot,row,col,piece->getType(1),piece->getType(2));
    				float boardwidth = (columns*size);
    	    		piece->nextPiece();
    	    	    piece->newPiece(start,height*.1,0);
    	    	    piece->setRow(0);
    	    	    piece->setCol(0);
    	    	    timer->resetTimer();
    	}

    	}
    	//else add to board
    }


	glPushMatrix();
	bground->render();
	glPopMatrix();
	piece->render();
	board->render();
	glPopMatrix();
	board->checkHorizontal();
	board->checkVertical();
}
bool GLscene::movePossible(){
	int row;
	int col;
	int rot = piece->getRotation();
	row =piece->getRow()+1;
	col = piece->getCol();

	if(row < rows && piece->getY()+size <= height  && checkBoardCollision(row,col,rot))
		return true;

	return false;
}
bool GLscene::checkBoardCollision(const int row, const int col,const int arot) const
{
    int startrow = row-1;
    int startcol = col;
    int rot = arot;

    for (int i = 0; i<3; i++){
	int currcol=startcol;
	for(int j=1; j<3; j++){
	    if(piece_types::pieces[rot][i][j] != 0){
		if(!board->isFree(startrow,currcol))
		    return false;
	    }
	    currcol+=1;
	}
	    startrow+=1;
    }
    return true;
}
bool GLscene::checkWallCollision()
{
    if(!piece->getX()-size >= start)
	return true;
    else if(!piece->getMaxX()+size <= end)
	return true;
    //returns true if there is a collision
    return false;
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
    //start at 90 percent of the screen for title
    size = (height*.9)/rows*1.0;
    float center = width/2;
    float boardwidth = (columns*size);
    start = center - (boardwidth/2);
   
    end = start +(size *columns);
    //add a little space on each side for the white line
    bground = new background(width,height,start-1,end+1);
    piece = new Piece();
    board = new Board(rows,columns,size,start,height*.1,width,height);
    piece->setSize(size);
    piece->setCoords(start,height*.1);
    piece->setRow(0);
    piece->setCol(0);
    timer = new SDLTimer();
    timer->setTimer(800);



}

GLscene::~GLscene()
{
    delete piece;
    delete bground;
    delete timer;

}
