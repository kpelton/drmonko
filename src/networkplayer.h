//Copyright (c) 2011 Kyle Pelton
//See COPYING for license information
#ifndef NETWORKPLAYER_H
#define NETWORKPLAYER_H
#include <math.h>
#include <time.h>
#include "player.h"
#include "netgame.h"
#include <SDL/SDL_net.h>
#include "types.h"
#include "timer.h"
#include "MenuWindow.h"
class NetPlayer: public Player
{
 public:
    virtual void renderScene(SDL_Event *event);
    NetPlayer(int width,int height,float size,float center,
	      float boardwidth,float start,float end
	      ,player_types::p_type type,string host);
	
    virtual ~NetPlayer();
    bool isDone();
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
    MenuWindow *menu;
    SDLTimer timer;
    int width;
    int height;
};

enum netmsg
    {
	UPDATE,
	SEED,
	NEWGAME,
	NEWPIECE,
	GAMEOVER,
	CONNECT,
	NETWIN,
	PAUSE,
	PONG,
    };
#endif
