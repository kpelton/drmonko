#ifndef BOARD_H
#define BOARD_H
#include "GLobject.h"
#include "GLscene.h"

//This is the class definition for the current piece
class Board : public GLobject
{
public:
	
    Board();
    Board(const int trows,const int cols,const float size,
	     const float xstart, const float ystart,
	  const int width,const int height);
    bool loadTextures();
    bool resize(){return false;};
    int  timerCb(){return 0;};
    bool render();
    void clear();
    bool isFree(const int row,const int col)const;
 private:
    GLuint tiles[4];
    float size;
    float xstart;
    float ystart;
    int nrows;
    int ncolumns;
    int width;
    int height;
    static const int rows = 20;
    static const int columns = 10;
    enum ptype{
	VIRUSRED,
	VIRUSBLUE,
	VIRUSYELLOW,
	PILLRED,
	PILLBLUE,
	PILLYELLOW,
	NOTHING =-1,
    };
    //void doColor(const int ctype)const;
    ptype board[rows][columns];
};
#endif
