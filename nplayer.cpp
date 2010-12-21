#include "nplayer.h"
#include "player.h"
#include "types.h"
#include "assert.h"
#include <string>

static const int port = 2010;
nplayer::nplayer(const int width, const int height, const player_types::p_type type, string address):player(width,height,type)
{
	Uint32 now;
	netgameboard  = new board(width,height,((height/20)*14) +1);
	waiting = true;
	wins = 0;
	losses = 0;
	now = SDL_GetTicks();
	host = address;
	seq = 1;
	lseq=0;
	channel=0;
	initClient();
	start = now+interval;

	sendMesg(net_cmd[PING].c_str());

}
nplayer::nplayer(const int width, const int height, const player_types::p_type type):player(width,height,type)
{
	Uint32 now;
	now = SDL_GetTicks();
	netgameboard  = new board(width,height,((height/20)*14)+1);
	waiting = true;
	lines = 0;
	wins = 0;
	losses = 0;
	seq = 1;
	lseq=0;
	initServer();


	start = now+interval;

}


void nplayer::waitLoop()
{
	handleCommands();
}

void nplayer::sendMesg(const char *msg)
{
	gpacket *packet;

	packet = new gpacket(sd,srvadd,channel,seq,msg,strlen(msg)+1);

	packets.insert(std::pair<Uint32,gpacket *>(seq,packet));
	seq++;

}

void nplayer::scanPackets()
{
	map<Uint32,gpacket*>::iterator it = packets.begin();

	for(; it != packets.end(); ++it)
	{
		it->second->checkUpdate();

	}
}


void nplayer::handleCommands()
{
	UDPpacket *p = NULL;
	int x = 5+sizeof(Uint32); //where the data starts in a gameboard packet;
	board *gameboard = player::getBoard();
	Uint32 score=0;
	Uint32 *ptr=NULL;
	char *cmd;
	Uint32 rseq;
	if (!(p = SDLNet_AllocPacket(1024)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(1);
	}
	if (SDLNet_UDP_Recv(sd, p))
	{

	if (p->data[0] == '$')
	{

		ptr = (Uint32*)&p->data[1];
		memcpy(&rseq,ptr,sizeof(Uint32));
		if(packets.find(rseq) != packets.end()){
				packets.erase (packets.find(rseq));
		}
		cout << "ACK:" << rseq <<endl;
	}

	else if(p->data[0] == '*')
	{
		ptr = (Uint32*)&p->data[1];
		memcpy(&rseq,ptr,sizeof(Uint32));
		cmd = (char *)p->data + sizeof(Uint32) + 1;
		srvadd.host =p->address.host;
		srvadd.port =p->address.port;
		channel = p->channel;

		gpacket::ack(sd,srvadd,channel,rseq);


		{

		if(strcmp(net_cmd[PING].c_str(),cmd) == 0  && waiting && rseq !=lseq)
		{
			player::getBoard()->clearBoard();
			netgameboard->clearBoard();

			sendMesg(net_cmd[PONG].c_str());
			cout <<"ping" <<endl;

		}


		else if( strcmp(net_cmd[PONG].c_str(),cmd) == 0 && waiting && rseq !=lseq)
		{

			player::getBoard()->clearBoard();
			netgameboard->clearBoard();

			sendMesg(net_cmd[START].c_str());
			waiting = false;
			cout <<"pong" <<endl;

		}

		else if(strcmp(net_cmd[START].c_str(),cmd) == 0 &&waiting && rseq !=lseq)
		{
			player::getBoard()->clearBoard();
			netgameboard->clearBoard();
			waiting = false;
		}
		else if(strcmp(net_cmd[LOSS].c_str(),cmd) == 0 && !waiting && rseq !=lseq)
		{
			waiting = true;
			cout <<"Loss" <<endl;
			wins++;


		}
		else if(cmd[0] == '^' && rseq !=lseq)
		{
			cout <<"Got Lines" <<endl;
			gameboard->addLines(cmd[1]);
		}
		else{
		cerr << "unknown packet!\n";



		}
		lseq = rseq;
		}
	}


		else if(p->data[0] == '~' && !waiting)
		{
			netgameboard->getNewPiece().ntype = p->data[1];
			netgameboard->setLines(p->data[2]);
			netgameboard->setLevel(p->data[3]);
			//copy 4 byte uint from the packet into an
			ptr = (Uint32*)&p->data[4];
			memcpy(&score,ptr,sizeof(Uint32));

			netgameboard->setScore(score);
			for (int i=0; i<gameboard->ROWWIDTH; i++)
			{
				for (int j=0; j<gameboard->COLUMNLENGTH; j++)
				{
					netgameboard->gameboard[i][j] = p->data[x];
					x++;
				}
			}

		}

		else{
			fprintf(stderr, "Unknown packet recieved\n");
		}
	}
	SDLNet_FreePacket(p);	
}



void nplayer::sendLines(const int lines)
{
	gpacket *packet;
	char *data = NULL;

	data = new char[2];
	data[0] = '^';
	data[1] = lines;

	packet = new gpacket(sd,srvadd,channel,seq,data,2);
	packets.insert(std::pair<Uint32,gpacket *>(seq,packet));
	seq++;
}

void nplayer::sendBoard(){

	board *gameboard = player::getBoard();
	UDPpacket *p = NULL;       /* Pointer to packet memory */
	string boardstr = "";
	int x=5+sizeof(Uint32);//where the gameboard starts in the packet
	Uint8 aboard[gameboard->ROWWIDTH][gameboard->COLUMNLENGTH];
	Uint32 score=0;
	Uint32* ptr=NULL;

	if (!(p = SDLNet_AllocPacket(1024)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(1);
	}
	p->data[0] = '~';

	for (int i=0; i<gameboard->ROWWIDTH; i++)
	{
		for (int j=0; j<gameboard->COLUMNLENGTH; j++)
		{
			aboard[i][j] = gameboard->gameboard[i][j];
		}
	}
	gameboard->addToBoard(aboard);

	p->data[1] = gameboard->getNewPiece().ntype;

	p->data[2] = gameboard->getLines();
	p->data[3] = gameboard->getLevel();
	score  = gameboard->getScore();

	ptr = (Uint32*)&p->data[4];
	memcpy(ptr, &score,sizeof(Uint32));

	for (int i=0; i<gameboard->ROWWIDTH; i++)
	{
		for (int j=0; j<gameboard->COLUMNLENGTH; j++)
		{
			p->data[x]  = aboard[i][j]; //copy board too packet
			x++;
		}
	}

	//send next piece in packet



	if(x){
		p->address.host = srvadd.host;	/* Set the destination host */
		p->address.port = srvadd.port;	/* And destination port */
		p->len = x;
		SDLNet_UDP_Send(sd, channel, p);
	}		
	SDLNet_FreePacket(p);	
}



nplayer::~nplayer()
{
	map<Uint32,gpacket*>::iterator it = packets.begin();

				for(; it != packets.end(); ++it)
				{
					delete it->second;

				}
	delete netgameboard;
}


void nplayer::initServer()
{
	/* Initialize SDL_net */
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	/* Open a socket */
	if (!(sd = SDLNet_UDP_Open(port)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
}


void nplayer::initClient()
{
	UDPpacket *p;

	/* Open a socket on random port */
	if (!(sd = SDLNet_UDP_Open(0)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}



	/* Resolve server name  */
	if (SDLNet_ResolveHost(&srvadd, host.c_str(), port) ==-1)
	{
		fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", host.c_str(),port, SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	SDLNet_UDP_Bind(sd, 0, &srvadd);

	/* Allocate memory for the packet */
	if (!(p = SDLNet_AllocPacket(512)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

}

int nplayer::timerCb(){


	Uint32 now;
	now = SDL_GetTicks();
	int lines = 0;

	if (!waiting){
		lines = player::timerCb();
		if ( start <= now ) 
		{
			start = now+interval;
			sendBoard();

		}
		if(lines >1){
			sendLines(lines);
		}
		if(lines <0)
		{
			waiting = true;
			sendMesg(net_cmd[LOSS].c_str());
			sendMesg(net_cmd[PING].c_str());
			losses++;
		}


	}

	waitLoop();
	scanPackets();
	return lines;


}
void nplayer::drawWins() const
{
	char cscore[50];
	string s = "Wins:";
	board *gameboard = player::getBoard();

	sprintf(cscore,"%i",wins);
	s += cscore;

	gameboard->drawString(s,(player::getHeight() *.75)+25);

	sprintf(cscore,"%i",losses);
	s = "Wins:";
	s += cscore;
	netgameboard->drawString(s,(player::getHeight() *.75)+25);

}
bool nplayer::render() {

	player::render();

	if(!waiting)
	{
		netgameboard->render();
		drawWins();
	}
	return true;
}
void nplayer::handleKeyPress(SDL_keysym &keysym)
{

	Uint32 now;
	now = SDL_GetTicks();

	if(!waiting){
		player::handleKeyPress(keysym);
	}
}
