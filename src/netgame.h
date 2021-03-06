//Copyright (c) 2011 Kyle Pelton
//See COPYING for license information
#ifndef _NETGAME_H
#define _NETGAME_H
#include "twoplayer.h"
#include "types.h"
#include <SDL/SDL_net.h>
class NetTwoPlayer: public TwoPlayer
{
 public:

    NetTwoPlayer(int width,int height,float size,float center,
		 float boardwidth,float start,float end,
		 const int *keys,bool flip,TCPsocket csd );
    virtual ~NetTwoPlayer(){};
	
    void renderScene(SDL_Event *event);
    void setNetRowCol(const int row, const int col,const int rot);
    void setCurr(const int curr);
    void startGame(time_t seed);
      
    Status getStatus();
 private:
    Status handleNoEvent();
    Status handleStatus(const Status status);
    void handleKeys(player_types::key key);
    void handlePauseEvent(const string & selection);
    Uint32 lastcol;
    Uint32 lastrow;
    Uint32 lastrot;
    TCPsocket csd;
    Uint32 last;
    bool sent;
    

};
#endif
