#ifndef GPACKET_H
#define GPACKET_H
#include <iostream>
#ifdef _WIN32
#include <SDL/SDL_net.h>
#else
#include "SDL_net.h"
#endif

using namespace std;

class gpacket
{

public:
	gpacket();
	gpacket(UDPsocket& sd, IPaddress &add,Uint32 channel, Uint32 seq,const void *data,int len);
	~gpacket(){SDLNet_FreePacket(p);};

	void checkUpdate(); //if this returns delete it from list
	Uint32 getSeq()const {return seq;};
	static void ack(UDPsocket& sd, IPaddress &add,Uint32 channel, Uint32 seq)
	{
		UDPpacket *p;
		Uint32 *ptr=NULL;
		if (!(p = SDLNet_AllocPacket(1024)))
		{
			cerr << "SDLNet_AllocPacket: %s\n" << SDLNet_GetError();
			exit(1);
		}

		p->data[0] = '$';
		ptr = (Uint32*)&p->data[1];
		memcpy(ptr, &seq,sizeof(Uint32));
		//now copy payload into packet
		p->address.host = add.host;	/* Set the destination host */
		p->address.port = add.port;	/* And destination port */
		p->len = sizeof(Uint32) + sizeof(char);

		SDLNet_UDP_Send(sd, channel, p);
		SDLNet_FreePacket(p);
	}

private:
	void updateTimer(){start = SDL_GetTicks()+interval;};

	void sendPacket();
	Uint32 seq;
	Uint32 channel;
	static const Uint32 interval = 1000; //interval to re-send if response isn't received
	UDPsocket sd;
	IPaddress srvadd;
	Uint32 start;
	void * data;
	UDPpacket *p;

};










#endif
