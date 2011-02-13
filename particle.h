/*
 * Particle Engine
 *
 *  Created on: Feb 6, 2011
 *      Author: Kyle Pelton
 */

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
	Particle(const float x,const float y,const float vx,const float vy,
			const float r, const float g, const float b,const GLuint& texture);
	void render();
	void setLife(const float a){this->a = a;};

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
	Uint32 last;
	float time;
	static const float ay = 50.8;

};

class Explosion{

public:
	Explosion(const float x, const float y,GLuint& texture,const int seconds);
	bool render();
	virtual ~Explosion();
private:
	static const int count = 50;
	Particle *particles[count];
	Uint32 last;
	SDLTimer timer;

};



class ParticleEngine: public GLobject {
public:
	ParticleEngine();
	virtual bool render();
	virtual bool resize(){return true;};
	virtual bool loadTextures();
	virtual ~ParticleEngine();
	virtual int timerCb(){return 0;};
	void addExplosion(const int x, const int y);

private:
	list<Explosion *> explosions;
	GLuint texture;
};

#endif /* MENUWINDOW_H_ */
