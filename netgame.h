#ifndef _NETGAME_H
#define _NETGAME_H
#include "twoplayer.h"
#include "types.h"
#ifdef _WIN32
#include <SDL/SDL_net.h>
#else
#include "SDL_net.h"
#endif
class NetTwoPlayer: protected TwoPlayer
{
public:

      NetTwoPlayer(int width,int height,float size,float center,
			float boardwidth,float start,float end, int argc,
		   char **argv , const int *keys,bool flip,TCPsocket csd);
      virtual ~NetTwoPlayer(){};
	
      void renderScene(SDL_Event *event);
      void setNetRowCol(const int row, const int col,const int rot);
      void setCurr(const int curr);

private:
	Status handleNoEvent();
	void handleKeys(player_types::key key);
	void handlePauseEvent(const string & selection);
	Uint32 lastcol;
	Uint32 lastrow;
	Uint32 lastrot;
	TCPsocket csd;
	Uint32 last;
	
};
#endif
