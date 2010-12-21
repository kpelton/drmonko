#include "piece.h"
#include <stdlib.h>
#include <time.h>

using namespace piece_types;
piece::piece(){


	firstPiece(7);
}

void piece::firstPiece(const int middle)
{
  
	type = rand()%7;
	rotation = 0;	
	this->x =  7-abs(piecesInitialPosition[type][0][0]);
	
	this->y =  abs(piecesInitialPosition[type][0][1]);
	nextPiece();

}

void piece::nextPiece()
{
	srand(time(NULL));
	ntype = rand()%7;
	nrotation = 0;	
}
void piece::newPiece(const int x, const int y,const int middle)
{
	type = ntype;
	
	this->x =  middle;//-abs(piecesInitialPosition[type][0][0]);
	
	this->y =  abs(piecesInitialPosition[type][0][1]);

	rotation = nrotation;
	nextPiece();
	
}

int piece::getBlockType(int x, int y)
{
  return pieces[type][rotation][x][y];
}



