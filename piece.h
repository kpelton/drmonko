#ifndef PIECE_H
#define PIECE_H
//This is the class definition for the current piece
//This class does not actually render the piece
//Rendering will be done in PieceRender
class Piece
{
public:
	
    //roate();
    int getBlockType(int,int);
    Piece();
    void nextPiece();
    void firstPiece(const int middle);
    void newPiece(const int x, const int y,const int middle);
 private:
    float x;
    float y;
    //Piece types from 3 different colors
    int type2; //the block that doesn't move when rotated
    int type1; //the block that moves
    int rotation;
    //This will handle the next piece
    int ntype1;
    int ntype2;
    int nrotation;
	
};
namespace piece_types{
 
// Pieces definition
    enum type{
	RED,
	BLUE,
	YELLOW,
    };
const int pieces [4 /* rotation */ ][3 /* horizontal blocks */ ][3 /* vertical blocks */ ] =
{
   {
       {0, 1, 0},
       {0, 2, 0},
       {0, 0, 0},
   },
   {
       {0, 0, 0},
       {1, 2, 0},
       {0, 0, 0},
   },
   {
       {0, 0, 0},
       {0, 2, 0},
       {0, 1, 0},
   },
   {
       {0, 0, 0},
       {0, 2, 1},
       {0, 0, 0},
   }
};
}
#endif
