#include "game.h"
#include "types.h"
#include <iostream>

void Game::renderScene(SDL_Event *event) {
	player_types::key key;
	
		Uint8 *keystate = SDL_GetKeyState(NULL);
		if (!paused && !animation && event && event->type == SDL_KEYDOWN) {
			for (int i = 0; i < 6; i++) {
				//cast sdl key to own virtual key mapping
				if (keystate[keys[i]]) {
					key = static_cast<player_types::key> (i);
					handleKeys(key);
					break;
				}
			}
		}

		if (!paused && event == NULL)
			handleNoEvent();
		//ends here


		board->clearPieces();	

	//Do Actual drawing
	glPushMatrix();
	bground->render();
	bground->drawVirus(board->getVirusCount());
	glPopMatrix();
	glPushMatrix();
	pengine.render();
	piece->render();
	board->render();
	glPopMatrix();

	glPushMatrix();
	drawNextPiece();
	glPopMatrix();
	

}
void Game::addToBoard(){
    int row = piece->getRow();
    int col = piece->getCol();
    int rot = piece->getRotation();
    board->addToBoard(rot, row, col, piece->getType(1), piece->getType(
								       2));
    piece->newPiece(5, 1);
    timer->resetTimer();
  
    
}

void Game::handleNoEvent() {

	int row = piece->getRow();
	int col = piece->getCol();
	int rot = piece->getRotation();
	
	board->clearPieces();

	if (timer->isDone()) {
	   
		if (movePossible()) {
		     timer->resetTimer();
		     if (animation){
				
				if (board->getVirusCount() == 0)
					status = WIN; //set status to win so parent can handle win
			} else {
				piece->setRow(piece->getRow() + 1);
			
			}

		} else {
		    addToBoard();
		      if (!movePossible(0) || board->getVirusCount() == 0)
			  status = LOSS; //game is over
		      
		}

	}

}


void Game::addExplosion(int color){
    switch(color){
    case RED:
	pengine.addExplosion(piece->getX()+(piece->getSize()/2),piece->getY(),1.0,0.0,0.0);
	break;
    case YELLOW:
	pengine.addExplosion(piece->getX()+(piece->getSize()/2),piece->getY(),1.0,1.0,0.0);
	break;
    case BLUE:
	pengine.addExplosion(piece->getX()+(piece->getSize()/2),piece->getY(),0.0,0.0,1.0);
	break;
    default:
	break;
    }
    
}

void Game::addTrail(){ 
    //addExplosion(piece->getType1());
    //addExplosion(piece->getType2());
    

}

void Game::handleKeys(player_types::key key) {
	int row;
	int col;
	int rot = piece->getRotation();
	switch (key) {

	case player_types::LEFT:
		//only move it if doesn't go out of the board
		row = piece->getRow();
		col = piece->getCol() - 1;
		if (col >= 0 && checkBoardCollision(row, col, rot)) {
			piece->setCol(piece->getCol() - 1);
			addTrail();
			
		}
		break;
	case player_types::RIGHT:
		row = piece->getRow();
		col = piece->getCol() + 1;
		//only move it if doesn't go out of the board
		
		if (checkBoardCollision(row, col, rot)&& ( (rot %2 == 0 &&col <=9) || (rot %2==1 && col <=8 ))){
			piece->setCol(piece->getCol() + 1);
			addTrail();
		}
		break;
	case player_types::ROTATE:
		row = piece->getRow();
		col = piece->getCol();
		piece->rotLeft();
		rot = piece->getRotation();
		
		//if the move is not valid put it back to the way it was
		if (!checkBoardCollision(row, col, rot) || 
		    ((rot == 1) && col == 9) || (rot == 3 && col == 9)){
			piece->rotRight();
		}else{
		    addTrail();
		}
		break;
		
	case player_types::DOWN:
		if (movePossible()) {
			piece->setRow(piece->getRow() + 1);
			addTrail();
		}
		break;

	default:
		break;
	}
}

void Game::startGame(){
    piece->setCurr(0);
    piece->firstPiece(6);
    timer->setTimer(1000);
    animation = false;
    paused = false;
    this->keys = keys;
    status = INPROGRESS;
}
void Game::newGame() {
    startGame();
      	board->newGame();
	piece->newPiece(5, 1);
}
void Game::drawNextPiece() {
	//first get the colors of the next piece
	int type1 = piece->getNewPiece1();
	int type2 = piece->getNewPiece2();
	int rot = 2;
	piece->drawPiece(end + 50, (height * .9) * .27, rot, type1, type2);

}

bool Game::movePossible(int add) //default argument of one to add to piece
{
	int row;
	int col;
	int rot = piece->getRotation();
	row = piece->getRow() + add;
	col = piece->getCol();

	if (row <= rows && row > 0 && checkBoardCollision(row, col, rot))
		return true;

	return false;
}
bool Game::checkBoardCollision(const int row, const int col, const int arot) const {
	int startrow = row - 1;
	int startcol = col;
	int rot = arot;

	for (int i = 0; i < 3; i++) {
		int currcol = startcol;
		for (int j = 1; j < 3; j++) {
			if (piece_types::pieces[rot][i][j] != 0) {
				if (!board->isFree(startrow, currcol))
					return false;
			}
			currcol += 1;
		}
		startrow += 1;
	}
	return true;
}
bool Game::checkWallCollision() {
	if (piece->getCol() >= 0)
		return true;
	else if (piece->getCol() <= rows)
		return true;
	//returns true if there is a collision
	else
		return false;
}
Game::Game() {

}
Game::Game(const int width, const int height) :
	width(width), height(height) {
	bground = new boardview(width, height, width * .25, width * .25);
	paused = false;
}

Game::Game(const int width, const int height, float size, float center,
		float boardwidth, float start, float end, int argc, char **argv,
		const int *keys) :
	width(width), height(height) {
	//start at 90 percent of the screen for title
	this->size = size;
	this->start = start;
	this->end = end;
	//add a little space on each side for the white line
	bground = new boardview(width, height, start - 1, end + 1);
	piece = new Piece(size, start, height * .1, start, end, height * .1);
	board = new Board(rows, columns, size, start, height * .1, width, height);
	timer = new SDLTimer();
	this->keys = keys;
	timer->setTimer(400);
	animation = false;
	paused = false;
	newGame();

}

Game::~Game() {
	delete piece;
	delete bground;
	delete board;
	delete timer;

}
