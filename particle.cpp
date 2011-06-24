#include "particle.h"
#include <stdlib.h>

Particle::Particle(){


}
Particle::Particle(const float x,const float y,const float vx,const float vy,
			const float r, const float g, const float b,const GLuint& texture,const float gravity=50.0)
{
	this->texture = texture;
	setup(x,y,vx,vy,r, g, b,gravity);
}



void Particle::setup(const float x,const float y,const float vx,const float vy,
		const float r, const float g, const float b,const float gravity=50.0){

	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->r = r;
	this->g = g;
	this->b = b;
	this->gravity = gravity;
	a = 0.4;
	last = SDL_GetTicks();
	time=0;
	

}


void Particle::render()
{
	Uint32 current_time = SDL_GetTicks();
	float ftime = (current_time - last) / 1000.0f;
	time +=ftime;
	float posx = (vx *time)+ x;
	float posy = ((gravity*(time*time))/2)+(vy * time) + y;
	a -=.0001;
	
	last = current_time;
	curr_x = posx;
	curr_y= posy;

	glColor4f(r,g,b,a);
	
	glBegin(GL_POINTS);
	
	glVertex2f(posx,posy);
	glEnd();

	glColor4f(1.0,1.0,1.0,1.0);
}

Smoke::Smoke(float x,float y,GLuint& texture){
		timer.setTimer(10);
		this->texture = texture;
		this->x = x;
		this->y = y;
}
bool Smoke::render(){
	float vx;
	float vy;
	float nx;
	float ny;
	float r;
	float g;
	float b;

	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(25);


	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);

	for(unsigned int i= 0; i<particles.size(); i++){
		particles[i]->render();

		if (particles[i]->getY() >768 || particles[i]->getY() <0 ){
			vx = ((float)rand() / (float) RAND_MAX) *5.0; //random between 0 and 50 pixels per second
			vy = ((float)rand() / (float) RAND_MAX) *-5; //random between 0 and 20 pixels per second
			nx = rand() %2;
			ny = rand() %2;
			nx = (nx==1) ? 1: -1;
			vx*= nx;
			vy*= ny;
			r =211.0/255.0;
			g = 211.0/255.0;
			b = 211.0/255.0;
			particles[i]->setup(x,y,vx,vy,r,g,b,-10.0);

		}

		}

	if (timer.isDone()){
		if (particles.size() < (unsigned int) count){
			for(int i= 0; i<5; i++){
				r =211.0/255.0;
				g = 211.0/255.0;
				b = 211.0/255.0;
				vx = ((float)rand() / (float) RAND_MAX) *5.0; //random between 0 and 50 pixels per second
				vy = ((float)rand() / (float) RAND_MAX) *-20; //random between 0 and 20 pixels per second
				nx = rand() %2;
				ny = rand() %2;
				nx = (nx==1) ? 1: -1;
				vx*= nx;
				vy*= ny;

				particles.push_back(new Particle(x,y,vx,vy,
						r,g, b,texture,-20.0));
			}
		}
	}
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	return false;
}


Snow::Snow(GLuint& texture){

		timer.setTimer(200);

		this->texture = texture;
}
bool Snow::render(){
	float vx;
	float vy;
	float nx;
	float ny;
	float r;
	float g;
	float b;

	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(10);


	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);

	for(unsigned int i= 0; i<particles.size(); i++){
		particles[i]->render();

		if (particles[i]->getY() >768){
			vx = ((float)rand() / (float) RAND_MAX) *100.0; //random between 0 and 50 pixels per second
			vy = ((float)rand() / (float) RAND_MAX) *20; //random between 0 and 20 pixels per second
			nx = rand() %2;
			ny = rand() %2;
			nx = (nx==1) ? 1: -1;
			r = 1.0;
			g = 1.0;
			b = 1.0;
			particles[i]->setup(rand()%1024*1.0f,-10,vx,vy,r,g,b);

		}

		}

	if (timer.isDone()){
		if (particles.size() < (unsigned int) count){
			for(int i= 0; i<10; i++){
				r = 1.0;
				g = 1.0;
				b = 1.0;
				vx = ((float)rand() / (float) RAND_MAX) *50.0; //random between 0 and 50 pixels per second
				vy = ((float)rand() / (float) RAND_MAX) *20; //random between 0 and 20 pixels per second
				nx = rand() %2;
				ny = rand() %2;
				nx = (nx==1) ? 1: -1;
				vx*= nx;
				vy*= ny;

				particles.push_back(new Particle(rand()%1024*1.0f,-10,vx,vy,
						r,g, b,texture));
			}
		}
	}
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	return false;
}


Explosion::Explosion(const float x, const float y,GLuint& texture,const int seconds,float r,float g, float b){
	float vx;
	float vy;
	float nx;
	float ny;

	this->texture = texture;


	for(int i= 0; i<count; i++){
	        vx = ((float)rand() / (float) RAND_MAX) *100.0;
		vy = ((float)rand() / (float) RAND_MAX) *100.0;
		nx = rand() %2;
		ny = rand() %2;
		nx = (nx==1) ? 1: -1;
		ny = (ny==1) ? 1: -1;
		vx*= nx;
		vy*= ny;

		particles[i] = new Particle(x,y,vx,vy,
					    r,g, b,texture,-500.0);
	}
	timer.setTimer(seconds);
}


bool Explosion::render(){
	glBindTexture(GL_TEXTURE_2D, texture);
		glEnable(GL_POINT_SPRITE);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPointSize(10);
		glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
	for(int i= 0; i<count; i++)
	    {
		glPointSize(20);
		particles[i]->render();
	    }
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
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
	list<Effect *>::iterator it1;
	for (it1=explosions.begin(); it1!=explosions.end(); ++it1)
		delete *it1;

	glDeleteTextures(1, &texture);
}

void ParticleEngine::addExplosion(const float x, const float y,float r, float g, float b)
{
    explosions.push_back(new Explosion(x,y,texture,5000,r,g,b));
}

void ParticleEngine::startSnow(){

	explosions.push_back(new Snow(texture));

}

void ParticleEngine::startSmoke(float x, float y){

	explosions.push_back(new Smoke(x,y,texture));

}

bool ParticleEngine::loadTextures()
{
	GLobject::loadTextureFile("tiles/particle.bmp",&texture);
	return true;
}
bool ParticleEngine::render(){
	vector <list<Effect *>::iterator  > toDelete;
	list<Effect *>::iterator it;
	vector <list<Effect *>::iterator  >::iterator intit;
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
