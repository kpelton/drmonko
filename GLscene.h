#ifndef GL_SCENE
#define GL_SCENE
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <time.h>
#include "GLobject.h"
#include "piece.h"
#include "board.h"
#include "timer.h"
#include "boardview.h"

using namespace std;

static const int rows = 20;
static const int columns = 10;
class GLscene
{
public:
	virtual void renderScene(SDL_Event *event);
	GLscene(int width, int height);
	GLscene(int width,int height, int argc, char **argv);
	GLscene();

	virtual ~GLscene();
private:
	boardview *bground;
	Piece *piece;
	Board *board;
	int width;
	int height;
	float size;
	float end;
	float start;
	bool checkWallCollision();
	bool movePossible();
	bool checkBoardCollision(const int row, const int col,const int rot) const;
	void drawNextPiece();
	bool animation;
	SDLTimer * timer;
};
#endif
