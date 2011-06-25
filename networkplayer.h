#ifndef NETWORKPLAYER_H
#define NETWORKPLAYER_H
#include <math.h>
#include <time.h>
#include "player.h"
#include "netgame.h"
#ifdef _WIN32
#include <SDL/SDL_net.h>
#else
#include "SDL_net.h"
#endif
#include "types.h"

class NetPlayer: public Player
{
public:
        virtual void renderScene(SDL_Event *event);
	NetPlayer(int width,int height,float size,float center,
			float boardwidth,float start,float end, int argc,
		  char **argv,player_types::p_type type);
	
	virtual ~NetPlayer();
private:
	void setupServer();
	void serverWait();
	void setupClient();
	bool checkActivity();
	static const int PORT=52312;
	NetTwoPlayer *twoplayer;
	TCPsocket sd, csd;
	IPaddress ip, *remoteIP;
	player_types::p_type type;
	SDLNet_SocketSet set;
	const int *keys;
};

enum netmsg
    {
	UPDATE,
	SEED,
	NEWGAME,
	NEWPIECE,
	PAUSE,
    };
#endif
