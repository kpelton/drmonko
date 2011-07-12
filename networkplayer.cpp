//Copyright (c) 2011 Kyle Pelton
//See COPYING for license information
#include "networkplayer.h"
#include "netgame.h"
#include <stdio.h>

NetPlayer::NetPlayer(int width,int height,float size,float center,
		     float boardwidth,float start,float end,
		     player_types::p_type type,string host)
{
    
   
    
    this->type = type;

    ready = false;
    set=SDLNet_AllocSocketSet(2);
    keys=player_types::p1_keys;
    this->host = host;
    cout <<host <<endl;
   
    if (type == player_types::INTERNET_SERVER)
	setupServer();

    if (type == player_types::INTERNET_CLIENT)
	setupClient();

    twoplayer = new NetTwoPlayer(width,height,size,center,
				 boardwidth,start,end,NULL,true,csd);
    
    menu = new MenuWindow(width, height, "Starting new Game...", NULL);
    this->width = width;
    this->height = height;
    
}



void NetPlayer::sendData(void * data,int len){
    int result=0;

    result = SDLNet_TCP_Send(csd,data,len);
    if (result <= 0){

	cerr<< "SDL Net Error:" << SDLNet_GetError()<<endl;
	
	exit(1);
    } 
    

}
void NetPlayer::recvData(void * data,int len){
    int result=0;

    result = SDLNet_TCP_Recv(csd,data,len);
    if (result <= 0){

	cerr<< "SDL Net Error:" << SDLNet_GetError()<<endl;
	exit(1);
    } 
    
}


void NetPlayer::handleCmds(){
    netmsg msg;
    Uint32 row; 
    Uint32 col;
    Uint32 buffer;
    Uint32 rot;
    Uint32 curr;
    Status status;

    while(checkActivity()){
	recvData(&msg,sizeof(msg));
	//printf("Got Packet Type:%i\n",static_cast<int>(msg));
	switch(msg){
	
	    
	case UPDATE:
	    recvData(&buffer,sizeof(Uint32));
	    row = buffer & 0x0000000ff;
	    col = (buffer & 0x0000ff00)>>8;
	    rot = (buffer & 0x00ff0000)>>16;
	    twoplayer->setNetRowCol(col,row,rot);
	    break;

	case NEWPIECE:
	    cout <<"Got New Piece"<<endl;
	    recvData(&curr,sizeof(Uint32));
	    cout <<curr<<endl;
	    twoplayer->setCurr(curr);
	    break;

	case SEED:
	   
	    
	    recvData( &seed, sizeof(seed));
	    cout <<"Got Seed:"<< seed<<endl;
	    ready = false;
	    msg = NEWGAME;
    
	    sendData(&msg, sizeof(msg));
	    cout << "Sent New Game"<<endl;
	    twoplayer->startGame(seed);
	    ready = true;
	    break;

	case PAUSE:
	    ready = false;
	    timer.setTimer(5000);
	    status =  twoplayer->getStatus();
	    if (status == LOSS){
		delete menu;
		menu = new MenuWindow(width, height, "YOU LOSE", NULL);
	    }
	    if (status == WIN){
		delete menu;
		menu = new MenuWindow(width, height, "YOU WIN", NULL);	
	    }

	    break;
	case CONNECT:
	    ready = false;
	    timer.setTimer(5000);
	    msg = PAUSE;
	    sendData(&msg, sizeof(msg));
	    break;
	case GAMEOVER:
	    cout <<"Game over"<<endl;
	    timer.setTimer(5000);

	    delete menu;
	    menu = new MenuWindow(width, height, "YOU WIN", NULL);
	    ready = false;
	    msg = PAUSE;
	    sendData(&msg, sizeof(msg));
	    break;
	case NETWIN:
	    delete menu;
	    menu = new MenuWindow(width, height, "YOU LOSE", NULL);
	    
	    timer.setTimer(5000);
	    ready = false;
	    msg = PAUSE;
	    sendData(&msg, sizeof(msg));
	    break;
	case NEWGAME:
	    cout <<"New Game"<<endl;
	    twoplayer->startGame(seed);
	    ready = true;
	    break;
	case PONG:
	    cout <<"Pong"<<endl;
	    twoplayer->startGame(seed);
	    ready = true;
	    break;
	
	default:
	    cerr << "Should Never happen:" << msg <<endl ;
	    break;

	}
    }
 
}

void NetPlayer::renderScene(SDL_Event *event){
    bool ourkey = false;
    
    netmsg msg;
    if (event && event->type == SDL_KEYDOWN) {
	for (int i = 0; i < 6; i++) {
	    //cast sdl key to own virtual key mapping
	    if (event->key.keysym.sym == keys[i]) {
		ourkey = true;
	    }

	}
    }
    
    if (ready){
	if (ourkey)
	    twoplayer->renderScene(event);
	else
	    twoplayer->renderScene(NULL);
    } else{

    	menu->render();
	if (type == player_types::INTERNET_SERVER && timer.isDone()   )
	    {
		seed = time(NULL);
		msg = SEED;
		sendData(&msg, sizeof(netmsg));
		sendData(&seed, sizeof(Uint32));
		ready = true;
	    }
    }


    handleCmds();
   
}

bool NetPlayer::checkActivity(){
    int numready;
    numready=SDLNet_CheckSockets(set, 0);
    if(numready==-1) {
	printf("SDLNet_CheckSockets: %s\n", SDLNet_GetError());
	//most of the time this is a system error, where perror might help you.
	perror("SDLNet_CheckSockets");
    }else if(numready){
	return true;
    }
    return false;
}
void NetPlayer::setupClient(){
    netmsg msg = CONNECT;
    if (SDLNet_Init() < 0)
	{
	    fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
	    exit(EXIT_FAILURE);
	}
 
    /* Resolve the host we are connecting to */
    if (SDLNet_ResolveHost(&ip,host.c_str(), PORT) < 0)
	{
	    fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
	    exit(EXIT_FAILURE);
	}
 
    /* Open a connection with the IP provided (listen on the host's port) */
    if (!(csd = SDLNet_TCP_Open(&ip)))
	{
	    fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
	    exit(EXIT_FAILURE);
	}

    if(SDLNet_TCP_AddSocket(set,csd) ==-1) 
	printf("SDLNet_AddSocket: %s\n", SDLNet_GetError());
    sendData(&msg,sizeof(netmsg));
}

void NetPlayer::setupServer(){
    if (SDLNet_Init() < 0)
	{
	    fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
	    exit(EXIT_FAILURE);
	}
 
    /* Resolving the host using NULL make network interface to listen */
    if (SDLNet_ResolveHost(&ip, NULL, PORT) < 0)
	{
	    fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
	    exit(EXIT_FAILURE);
	}
 
    /* Open a connection with the IP provided (listen on the host's port) */
    if (!(sd = SDLNet_TCP_Open(&ip)))
	{
	    fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
	    exit(EXIT_FAILURE);
	}
    serverWait();
    

}
void NetPlayer::serverWait(){
    
    while(1){
	if ((csd = SDLNet_TCP_Accept(sd)))
	    {
		/* Now we can communicate with the client using csd socket
		 * sd will remain opened waiting other connections */
 
		/* Get the remote address */
		if ((remoteIP = SDLNet_TCP_GetPeerAddress(csd)))
		    /* Print the address, converting in the host format */
		    printf("Host connected: %x %d\n", SDLNet_Read32(&remoteIP->host), SDLNet_Read16(&remoteIP->port));
		else
		    fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
		break;
	    }
    }
    if(SDLNet_TCP_AddSocket(set,csd) ==-1) 
	printf("SDLNet_AddSocket: %s\n", SDLNet_GetError());

    
    
}
NetPlayer::~NetPlayer()
{
    delete twoplayer;
    delete menu;
}
