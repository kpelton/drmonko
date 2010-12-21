#include "gpacket.h"
#include <iostream>

using namespace std;

gpacket::gpacket(UDPsocket& sd, IPaddress &add, Uint32 channel,Uint32 seq,const void *data,int len)
{
	Uint32 *ptr=NULL;
	this->seq = seq;
	this->sd = sd;
	this->srvadd = add;
	this->channel = channel;


	if (!(p = SDLNet_AllocPacket(1024)))
	{
		cerr << "SDLNet_AllocPacket: %s\n" << SDLNet_GetError();
		exit(1);
	}

	p->data[0] = '*';
	ptr = (Uint32*)&p->data[1];
	memcpy(ptr, &this->seq,sizeof(Uint32));
	//now copy payload into packet
	memcpy(&p->data[1]+sizeof(Uint32), data ,len);
	p->address.host = srvadd.host;	/* Set the destination host */
	p->address.port = srvadd.port;	/* And destination port */
	p->len = len + sizeof(Uint32) + sizeof(char);
	sendPacket();
}
void gpacket::checkUpdate()
{
	Uint32 now;
	now = SDL_GetTicks();

	if ( start <= now )
		sendPacket();

}

void gpacket::sendPacket()
{
	cout <<"SYN:" <<seq <<endl;
	SDLNet_UDP_Send(sd, channel, p);
	updateTimer();
}


