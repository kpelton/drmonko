#ifndef SDL_WINDOW
#define SDL_WINDOW
#include <iostream>
#include <GL/gl.h>
#include <math.h>
#ifdef _WIN32
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#else
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#endif
#include "GLscene.h"
#include <time.h>


#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 768
#define SCREEN_BPP     32

class sdlWindow {

 public:
    sdlWindow();
    sdlWindow(int argc,char **argv);
    ~sdlWindow(){delete scene;};
    void initWindow();
    void initGL();
    void renderLoop();
    bool resizeWindow(const int width, const int height);
	

 private:
    int videoFlags;
    bool done;
    SDL_Event event;
    const SDL_VideoInfo *videoInfo;
    bool isActive;
    SDL_Surface *surface;
    GLscene *scene;
    int width;
    int height;
    bool fullscreen;
    static const char *musicFile;
	
    Uint32 GameLoopTimer(Uint32 interval, void* param);
};
#endif
