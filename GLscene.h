#ifndef GL_SCENE
#define GL_SCENE
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <time.h>
#include "GLobject.h"

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
	GLobject *bground;
	int width;
	int height;
};
#endif
