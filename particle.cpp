#include "particle.h"
#include <stdlib.h>

Particle::Particle(const float x,const float y,const float vx,const float vy,
			const float r, const float g, const float b,const GLuint& texture)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->r = r;
	this->g = g;
	this->b = b;
	a = 1.0;
	this->texture = texture;
	last = SDL_GetTicks();
	time=0;
}

void Particle::render()
{
	Uint32 current_time = SDL_GetTicks();
	float ftime = (current_time - last) / 1000.0f;
	time +=ftime;
	float posx = (vx *time)+ x;
	float posy = ((ay*(time*time))/2)+(vy * time) + y;
	a-= 0.001;
	last = current_time;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(10);
	glPushMatrix();
	glColor4f(r,g,b,a);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
	glBegin(GL_POINTS);
	glVertex2f(posx,posy);
	glEnd();
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glColor4f(1.0,1.0,1.0,1.0);
}
//class Explosion{
//
//public:
//	Explosion(const float x, const float y,GLUint texture,const int seconds)
//	virtual void render();
//
//private:
//	int life;
//	SDLtimer timer;
//	GLUint texture;
//	vector<Particle> options;
//
//};
//
//

Explosion::Explosion(const float x, const float y,GLuint& texture,const int seconds){
	float vx;
	float vy;
	float nx;
	float ny;
	float r;
	float g;
	float b;
	srand(time(NULL));



	for(int i= 0; i<count; i++){
		r = ((float)rand() / (float) RAND_MAX) *1.0;
		g = ((float)rand() / (float) RAND_MAX) *1.0;
		b = ((float)rand() / (float) RAND_MAX) *1.0;
		vx = ((float)rand() / (float) RAND_MAX) *500.0;
		vy = ((float)rand() / (float) RAND_MAX) *500.0;
		nx = rand() %2;
		ny = rand() %2;
		nx = (nx==1) ? 1: -1;
		ny = (ny==1) ? 1: -1;
		vx*= nx;
		vy*= ny;

		particles[i] = new Particle(x,y,vx,vy,
			r,g, b,texture);
	}
	timer.setTimer(seconds);
}

bool Explosion::render(){
	for(int i= 0; i<count; i++)
		particles[i]->render();
	if(timer.isDone())
		return true;
	return false;
}

Explosion::~Explosion(){
	for(int i= 0; i<count; i++)
		delete particles[i];
}

ParticleEngine::ParticleEngine()
{
	loadTextures();
}

ParticleEngine::~ParticleEngine()
{
	//delete all explosions
	list<Explosion *>::iterator it1;
	for (it1=explosions.begin(); it1!=explosions.end(); ++it1)
		delete *it1;

	glDeleteTextures(1, &texture);
}

void ParticleEngine::addExplosion(const int x, const int y)
{
	 explosions.push_back(new Explosion(x,y,texture,5000));
}

bool ParticleEngine::loadTextures()
{
	GLobject::loadTextureFile("tiles/particle.bmp",&texture);
	return true;
}
bool ParticleEngine::render(){
	vector <list<Explosion *>::iterator  > toDelete;
	list<Explosion *>::iterator it;
	vector <list<Explosion *>::iterator  >::iterator intit;
	for (it=explosions.begin(); it!=explosions.end(); ++it){
	    if((*it)->render()){ //explosion is ready to be removed
	    	std::cout << "added"<<endl;
	    	toDelete.push_back(it);
	    }

	}
	for (intit= toDelete.begin(); intit!=toDelete.end(); ++intit)
		explosions.erase(*intit);


	return true;

}


//
//class ParticleEngine: public GLobject {
//public:
//	ParticleEngine();
//	virtual bool render();
//	virtual bool resize(){return true;};
//	virtual bool loadTextures(){return true;};
//	virtual ~ParticleEngine();
//	virtual int timerCb(){return 0;};
//
//private:
//	vector<Explosion *> explosions;
//
//};
