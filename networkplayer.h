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
	      char **argv,player_types::p_type type,string host);
	
    virtual ~NetPlayer();
 private:
    void setupServer();
    void serverWait();
    void setupClient();
    void handleCmds();
    bool checkActivity();
    void sendData(void * data,int len);
    void recvData(void * data,int len);
    static const int PORT=52312;
    NetTwoPlayer *twoplayer;
    TCPsocket sd, csd;
    IPaddress ip, *remoteIP;
    player_types::p_type type;
    SDLNet_SocketSet set;
    const int *keys;
    time_t seed;
    bool ready;
    string host;
};

enum netmsg
    {
	UPDATE,
	SEED,
	NEWGAME,
	NEWPIECE,
	GAMEOVER,
	PAUSE,
	PONG,
    };
#endif
