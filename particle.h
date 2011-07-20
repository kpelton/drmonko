//Copyright (c) 2011 Kyle Pelton
//See COPYING for license information
#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "GLobject.h"
#ifdef _WIN32
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_ttf.h>
#else
#include "SDL.h"
#include "SDL_ttf.h"
#endif
#include <vector>
#include <list>
#include <string>
#include "timer.h"
#include "types.h"

class Particle {

 public:
    Particle();
    Particle(const float x,const float y,const float vx,const float vy,
	     const float r, const float g, const float b,const GLuint& texture,const float gravity);
    void render();
    void setLife(const float a){this->a = a;};
    float getY(){return curr_y;};
    void setup(const float x,const float y,const float vx,const float vy,
	       const float r, const float g, const float b,const float gravity);
 private:
    GLuint texture;
    float x; //location
    float y; //location
    float vx;//velocity
    float vy;//velocity
    float r;
    float g;
    float b;
    float a; //life
    float curr_y;
    float curr_x;
    Uint32 last;
    float time;
    float gravity;
    static const float ay = 50.8; //acceleration in y direction(gravitiy)

};


class Effect {

 public:
    Effect(){};
    virtual ~Effect(){};
    virtual bool render() = 0;

};
class Explosion: public Effect{

 public:
    Explosion(const float x, const float y,GLuint& texture,const int seconds,float r, float g, float b);
    bool render();
    virtual ~Explosion();
 private:
    static const int count =  1;
    Particle *particles[count];
    Uint32 last;
    SDLTimer timer;
    GLuint texture;

};

class Snow: public Effect{

 public:
    Snow(GLuint& texture);
    bool render();
    //virtual ~Explosion();
 private:
    static const int count = 5000;
    vector <Particle *>particles;
    Uint32 last;
    SDLTimer timer;
    GLuint texture;


};


class Smoke: public Effect{

 public:
    Smoke(float x, float y,GLuint& texture);
    bool render();
    //virtual ~Explosion();
 private:
    static const int count = 100;
    vector <Particle *>particles;
    Uint32 last;
    SDLTimer timer;
    GLuint texture;
    float x;
    float y;

};


class ParticleEngine: public GLobject {
 public:
    ParticleEngine();
    virtual bool render();
    virtual bool resize(){return true;};
    virtual bool loadTextures();
    virtual ~ParticleEngine();
    void addExplosion(const float x, const float y,float r, float g, float b);
    void startSnow();
    void startSmoke(float x, float y);

 private:
    list<Effect *> explosions;
    GLuint texture;
};

#endif /* MENUWINDOW_H_ */
