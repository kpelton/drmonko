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

}
void Game::handleNoEvent() {

	int row = piece->getRow();
	int col = piece->getCol();
	int rot = piece->getRotation();

	if (timer->isDone()) {
		if (movePossible()) {
			if (animation) {
				animation = board->clearPieces();
				if (board->getVirusCount() == 0)
					status = WIN; //set status to win so parent can handle win
			} else {
				piece->setRow(piece->getRow() + 1);
			}

		} else {
			board->addToBoard(rot, row, col, piece->getType(1), piece->getType(
					2));
			piece->newPiece(5, 1);
			timer->resetTimer();
			if (!movePossible(0) || board->getVirusCount() == 0)
				status = LOSS; //game is over
		}

	}

}

void Game::handleKeys(player_types::key key) {
	int row;
	int col;
	int max;
	int rot = piece->getRotation();
	switch (key) {

	case player_types::LEFT:
		//only move it if doesn't go out of the board
		row = piece->getRow();
		col = piece->getCol() - 1;
		if (col >= 0 && checkBoardCollision(row, col, rot)) {
			piece->setCol(piece->getCol() - 1);
		}
		break;
	case player_types::RIGHT:
		row = piece->getRow();
		col = piece->getCol() + 1;
		//only move it if doesn't go out of the board
		max = piece->getMaxX()+size; //hack
		if (max <= end && checkBoardCollision(row, col, rot)){
			piece->setCol(piece->getCol() + 1);
		}
		break;
	case player_types::ROTATE:
		row = piece->getRow();
		col = piece->getCol();
		piece->rotLeft();
		rot = piece->getRotation();

		//if the move is not valid put it back to the way it was
		if (!checkBoardCollision(row, col, rot) || piece->getMaxX() > end)
			piece->rotRight();
		break;
	case player_types::DOWN:
		if (movePossible()) {
			piece->setRow(piece->getRow() + 1);
		}
		break;

	default:
		break;
	}
}

void Game::newGame() {
	piece->nextPiece();
	piece->nextPiece();
	board->newGame();
	piece->newPiece(5, 1);
	timer->setTimer(400);
	animation = false;
	paused = false;
	this->keys = keys;
	status = INPROGRESS;

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
