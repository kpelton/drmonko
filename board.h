#ifndef BOARD_H
#define BOARD_H
#include "GLobject.h"
#include "piece.h"
#include "particle.h"
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
	PILL,
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
    ~Board(){glDeleteTextures(5, tiles);};
    bool loadTextures();
    bool resize(){return false;};
    bool render();
    void clear();
    bool isFree(const int row,const int col)const;
    void addToBoard(const int rotation,const int row,const int col,const int type1, const int type2);
    int getVirusCount() const{return viruses;};
    void newGame();
    bool clearPieces();
 private:
    void drawPill(const float x,const float y,const int row,const int col) const;
    GLuint tiles[5];
    float size;
    float xstart;
    float ystart;
    int nrows;
    int ncolumns;
    int width;
    int height;
    int viruses;
    ParticleEngine pengine;
    static const int rows = 20;
    static const int columns = 10;
    struct BoardPlace{
    	BoardPlace(){clear();};
    	void clear(){type=NOTHING;col=RED;rot=NONE;};
    	BoardPlace & operator= (const  BoardPlace & other){type = other.type; col=other.col; rot=other.rot; return *this;};
    	ptype  type;
    	color col;
    	rotation rot;
    };
    //void doColor(const int ctype)const;
    void removeMatchHorizontal(const int row, const int startcol);
    void removeMatchVertical(const int col, const int startrow);
    void changePillType(const int row, const int col);
    void checkHorizontal();
    void checkVertical();
    bool moveDown();


    BoardPlace board[rows][columns];
};
#endif
