//Copyright (c) 2011 Kyle Pelton
//See COPYING for license information
#ifndef TIMER_H
#define TIMER_H
#include <SDL/SDL.h>


class SDLTimer{
 public:
    bool isDone();
    void resetTimer();
    void setTimer(const int interval);

 private:
    int interval;
    Uint32 last;
};


#endif
