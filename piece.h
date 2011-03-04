#ifndef PIECE_H
#define PIECE_H
#include "GLobject.h"
//This is the class definition for the current piece

class Piece : public GLobject
{
public:
	
    //roate();
    int getBlockType(int,int);
    Piece(const float & size,const float& x,const float& y,const float& left,const float& right,const float &top);
    // startx starty. xcoord of board left xcord of boardright
    ~Piece(){glDeleteTextures(1, &texture);};
    void nextPiece();
    void firstPiece(const int middle);
    void newPiece(const int row, const int col);
    bool loadTextures();
    bool resize(){return false;};
    bool render();

    int getRotation()const {return rotation;};
    void setRotation(const int rot) {rotation=rot;};
    void rotLeft();
    void rotRight();

    float getMaxX()const; //this function deals with coordinates and needs to be changed to rows/cols
    int getRow()const{return row;}
    void setRow(const int arow);
    int getCol()const{return col;}
    void setCol(const int acol);
    void setSize(const float isize){size=isize;};
    bool drawPiece(float px, float py,int rot,int ty1,int ty2);
    int getNewPiece1() const {return ntype1;} ;
    int getNewPiece2() const {return ntype2;} ;


    int getType(const int num);

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
    int row;
    int col;
    float left;
    float right;
    float top;
    void setCoords(const float x, const float y){this->x=x;this->y=y;};
    float getX() {return x;};
    float getY(){return y;};
    float size;
    int nrotation;
    GLuint texture;
    void doColor(const int ctype)const;
    // Pieces definition
    enum type{
	RED,
	BLUE,
	YELLOW,
    };
};
namespace piece_types{
 

const int pieces [4 /* rotation */ ][3 /* horizontal blocks */ ][3 /* vertical blocks */ ] =
{
   {
       {0, 1, 0},
       {0, 2, 0},
       {0, 0, 0},
   },
   {
       {0, 0, 0},
       {0, 2, 1},
       {0, 0, 0},
   },
   {
       {0, 2, 0},
       {0, 1, 0},
       {0, 0, 0},
   },
   {
       {0, 0, 0},
       {0, 1, 2},
       {0, 0, 0},
   }
};
}
#endif
