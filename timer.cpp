#include "timer.h"


void SDLTimer::setTimer(const int ainterval)
{

	interval = ainterval;
	last = SDL_GetTicks();

}

bool SDLTimer::isDone()
{
	if (last+interval <= SDL_GetTicks()){
		resetTimer();
		return true;
	}
	return false;

}
void SDLTimer::resetTimer(){
	last = SDL_GetTicks();

}
