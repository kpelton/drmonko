#ifndef GL_SCENE
#define GL_SCENE
#include <GL/gl.h>
#include "GLobject.h"
#include "game.h"
#include "player.h"
#include "splayer.h"
#include "twoplayer.h"
#include "networkplayer.h"
#include "types.h"
#include "MenuWindow.h"


class GLscene
{
public:
	virtual void renderScene(SDL_Event *event);
	GLscene(int width,int height, int argc, char **argv);

	virtual ~GLscene();
private:
	int width;
	int height;
	Player *game;
	Game *rightgame;
	TTF_Font *font;
	MenuWindow *menu;
	void setupGame();
};
#endif
