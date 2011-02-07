#ifndef GL_SCENE
#define GL_SCENE
#include <GL/gl.h>
#include <GL/glu.h>
#include "GLobject.h"
#include "game.h"
#include "MenuWindow.h"


class GLscene
{
public:
	virtual void renderScene(SDL_Event *event);
	GLscene(int width, int height);
	GLscene(int width,int height, int argc, char **argv);
	GLscene();

	virtual ~GLscene();
private:
	int width;
	int height;
	Game *leftgame;
	Game *rightgame;
	TTF_Font *font;
	MenuWindow *menu;
	void setupGame();
};
#endif
