#ifndef BOARD_H
#define BOARD_H
#include "GLobject.h"
#include "GLscene.h"
namespace types {
enum rotation{
	UP,
	LEFT,
	DOWN,
	RIGHT,
	NONE=-1,
};
enum color{
	RED,
	BLUE,
	YELLOW,
	BLANK,
};
enum ptype{
	VIRUS,
	SETPILL,
	NOTHING =-1,
  };
}
using namespace types;
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
    void addToBoard(const int rotation,const int row,const int col,const int type1, const int type2);
    void checkHorizontal();
    void checkVertical();
 private:
    void drawPill(const float x,const float y,const int row,const int col) const;
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
    static const int PILL=3;
    struct BoardPlace{
    	BoardPlace(){clear();};
    	void clear(){type=NOTHING;col=RED;rot=NONE;};
    	ptype  type;
    	color col;
    	rotation rot;
    };
    //void doColor(const int ctype)const;
    void removeMatchHorizontal(const int row, const int startcol);
    void removeMatchVertical(const int col, const int startrow);
    void changePillType(const int row, const int col);

    BoardPlace board[rows][columns];
};
#endif
