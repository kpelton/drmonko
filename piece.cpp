#include "piece.h"
#include <stdlib.h>
#include <time.h>

using namespace piece_types;
Piece::Piece()
{
    firstPiece(7);
}

void Piece::firstPiece(const int middle)
{
  	type1 = rand()%3;
	type2 = rand()%3;
	rotation = 0;	
	nextPiece();
}

void Piece::nextPiece()
{
	srand(time(NULL));
	ntype1 = rand()%3;
	ntype2 = rand()%3;
	nrotation = 0;	
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



