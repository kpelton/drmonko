#ifndef GL_SCENE
#define GL_SCENE
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <time.h>
#include "GLobject.h"
#include "player.h"

#include <vector>

using namespace std;



class GLscene
{
public:
	virtual void renderScene(SDL_Event *event);
	GLscene(int width, int height);
	GLscene(int width,int height, int argc, char **argv);
	GLscene();

	virtual ~GLscene();
private:
	GLobject *player1;
	GLobject *player2;
	int width;
	int height;

};
#endif
