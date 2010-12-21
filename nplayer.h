#ifndef NPLAYER_H
#define NPLAYER_H
#include "player.h"
#include "types.h"
#include "board.h"
#include "gpacket.h"
#include <iostream>
#include <map>
#ifdef _WIN32
#include <SDL/SDL_net.h>
#else
#include "SDL_net.h"
#endif

enum cmds{
	PING,
	PONG,
	START,
	LINES,
	LINESACK,	
	LOSS,
};
static const string net_cmd [] = {"PING",
				   "PONG",
				   "START",
				   "^",
				   "^ACK",
				   "!"};

class nplayer : public player
{
 
public:

	nplayer(){

	};
	~nplayer();
        nplayer(const int width, const int height, const player_types::p_type type ,string address);
	nplayer(const int width, const int height, const player_types::p_type type);
	void handleKeyPress(SDL_keysym &keysym);
	bool render();
	int timerCb();
	

private:
	void waitLoop();
	void initServer();
	void initClient();
	void sendBoard();
	void scanPackets();
	void handleCommands();
	void sendMesg(const char *msg);
	void sendLines(const int lines);
	void drawWins() const;
	board *netgameboard;
	bool waiting;
	string host;
	UDPsocket sd;
	UDPsocket cd;
	IPaddress srvadd;
	IPaddress cliadd;
	int channel;
	Uint32 lines;
	Uint32 wins;
	Uint32 losses;
	Uint32 start;
	Uint32 seq;
	Uint32 lseq;
	static const Uint32 interval = 30;
	map <Uint32,gpacket*> packets;

         }; 
#endif
