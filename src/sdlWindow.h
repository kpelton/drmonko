//Copyright (c) 2011 Kyle Pelton
//See COPYING for license information
#ifndef SDL_WINDOW
#define SDL_WINDOW
#include <iostream>
#include <GL/gl.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "GLscene.h"
#include <time.h>


#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080
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
    	
    Uint32 GameLoopTimer(Uint32 interval, void* param);
};
#endif
