#include "game.h"
#include "types.h"
#include <iostream>


void Game::renderScene(SDL_Event *event)
{
	player_types::key key;


	if (menu){
		if(menu->handleEvent(event)){

			handlePauseEvent(menu->getSelected());
		}

	}else{
		//All Logic hapens here
		if( !animation && event && event->type == SDL_KEYDOWN){
			for(int i=0; i<6; i++){
				//cast sdl key to own virtual key mapping
				if(event->key.keysym.sym == keys[i]){
					key = static_cast<player_types::key>(i);
					handleKeys(key);
					break;
				}
			}
		}


		if(event == NULL)
			handleNoEvent();
		//ends here
	}

	//Do Actual drawing
	glPushMatrix();
	bground->render();
	bground->drawVirus(board->getVirusCount());
	glPopMatrix();
	glPushMatrix();
	piece->render();
	board->render();
	glPopMatrix();
	if (!animation)
		animation = board->clearPieces();
	glPushMatrix();
	drawNextPiece();
	glPopMatrix();
	if(menu)
		menu->render();
}

void Game::handlePauseEvent(const string & selection){
	if (menu->getSelected() == "Resume"){
		delete menu;
		menu = NULL;
	}
	else if (menu->getSelected() == "Exit"){
		SDL_Quit();
	}

}
void Game::handleNoEvent()
{

	int row =piece->getRow();
	int col = piece->getCol();
	int rot = piece->getRotation();

	if (timer->isDone()){
		if (movePossible()){
			if (animation){
				animation = board->clearPieces();
			}else{
				piece->setCoords(piece->getX(),piece->getY()+size);
				piece->setRow(piece->getRow()+1);
			}

		}else{
			board->addToBoard(rot,row,col,piece->getType(1),piece->getType(2));
			piece->newPiece(start,height*.1,0);
			timer->resetTimer();
		}

	}

}

void Game::handleKeys(player_types::key key )
{
	int row;
	int col;
	int rot = piece->getRotation();
	switch(key){

	    case player_types::LEFT:
		//only move it if doesn't go out of the board
		row =piece->getRow();
		col = piece->getCol()-1;
		if(col >=0 && checkBoardCollision(row,col,rot)){
		    piece->setCoords(piece->getX()-size,piece->getY());
		    piece->setCol(piece->getCol()-1);
		}
		break;
	    case player_types::RIGHT:
		row =piece->getRow();
		col = piece->getCol()+1;
		//only move it if doesn't go out of the board
		if(piece->getMaxX()+size <= end  && checkBoardCollision(row,col,rot) ){
		    piece->setCoords(piece->getX()+size,piece->getY());
		    piece->setCol(piece->getCol()+1);
		}
		break;
	    case player_types::ROTATE:
		row =piece->getRow();
		col = piece->getCol();
		piece->rotLeft();
		rot = piece->getRotation();

		//if the move is not valid put it back to the way it was
		if (!checkBoardCollision(row,col,rot) || piece->getMaxX() > end)
		    piece->rotRight();
		break;
	    case player_types::DOWN:
	    	if (movePossible()){
	    		piece->setCoords(piece->getX(),piece->getY()+size);
	    		piece->setRow(piece->getRow()+1);
	    	}
		break;
	    case player_types::EXIT:
	    	menu  = new MenuWindow(width,height,"Paused",NULL);
	    	menu->addOption("Resume");
	    	menu->addOption("Exit");

	    default:
		break;
	    }
}

void Game::drawNextPiece()
{
	//first get the colors of the next piece
	int type1 = piece->getNewPiece1();
	int type2 = piece->getNewPiece2();
	int rot = 2;
	piece->drawPiece(end+50,(height*.9) *.27 ,rot,type1,type2);


}

bool Game::movePossible()
{
	int row;
	int col;
	int rot = piece->getRotation();
	row =piece->getRow()+1;
	col = piece->getCol();

	if(row < rows && piece->getY()+size <= height  && checkBoardCollision(row,col,rot))
		return true;

	return false;
}
bool Game::checkBoardCollision(const int row, const int col,const int arot) const
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
bool Game::checkWallCollision()
{
    if(!piece->getX()-size >= start)
    	return true;
    else if(!piece->getMaxX()+size <= end)
    	return true;
    //returns true if there is a collision
    else
    	return false;
}
Game::Game()
{

}
Game::Game(const int width, const int height):width(width),height(height)
{
    bground = new boardview(width,height,width*.25,width*.25);
    paused = false;
    menu = NULL;
}

Game::Game(const int width, const int height,float size,float center,
		float boardwidth,float start,float end,
		int argc,char **argv,const int *keys):width(width),height(height)
{
    //start at 90 percent of the screen for title
    this->size = size;
    this->start = start;
    this->end = end;

    //add a little space on each side for the white line
    bground = new boardview(width,height,start-1,end+1);
    piece = new Piece(size,start,height*.1);
    board = new Board(rows,columns,size,start,height*.1,width,height);
    timer = new SDLTimer();
    timer->setTimer(400);
    animation = false;
    this->keys = keys;
    menu = NULL;



}

Game::~Game()
{
    delete piece;
    delete bground;
    delete board;
    delete timer;
    if (menu)
    	delete menu;

}
