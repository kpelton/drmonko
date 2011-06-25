#include "networkplayer.h"
#include "netgame.h"
#include <stdio.h>

NetPlayer::NetPlayer(int width,int height,float size,float center,
		     float boardwidth,float start,float end, int argc,
		     char **argv,player_types::p_type type)
{
    
   
    
    this->type = type;

    set=SDLNet_AllocSocketSet(2);
    keys=player_types::p1_keys;
    if (type == player_types::INTERNET_SERVER)
	setupServer();

    if (type == player_types::INTERNET_CLIENT)
	setupClient();

     twoplayer = new NetTwoPlayer(width,height,size,center,
				  boardwidth,start,end,argc,NULL,NULL,true,csd);
    
}
void NetPlayer::renderScene(SDL_Event *event){
    bool ourkey = false;
    int key = 0;
    SDL_Event user_event;
    netmsg msg;
    Uint32 row; 
    Uint32 col;
    Uint32 buffer;
    Uint32 rot;
    Uint32 curr;


    if (event && event->type == SDL_KEYDOWN) {
	for (int i = 0; i < 6; i++) {
	    //cast sdl key to own virtual key mapping
	    if (event->key.keysym.sym == keys[i]) {
		ourkey = true;
	    }

	}
    }
    
    if (ourkey)
	twoplayer->renderScene(event);
    else
	twoplayer->renderScene(NULL);
    while(checkActivity()){
	SDLNet_TCP_Recv(csd,&msg,sizeof(msg));
	printf("Got Packet Type:%i\n",static_cast<int>(msg));
	if(msg == UPDATE){
	    SDLNet_TCP_Recv(csd,&buffer,sizeof(Uint32));
	    row = buffer & 0x0000000ff;
	    col = (buffer & 0x0000ff00)>>8;
	    rot = (buffer & 0x00ff0000)>>16;
	    twoplayer->setNetRowCol(col,row,rot);
	}

	if(msg == NEWPIECE){
	    cout <<"Got New Piece"<<endl;
	    SDLNet_TCP_Recv(csd,&curr,sizeof(Uint32));
	    cout <<curr<<endl;
	    twoplayer->setCurr(curr);
	    

	}
    
    }
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
    unsigned int seed;
    netmsg msg;
 
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Resolve the host we are connecting to */
	if (SDLNet_ResolveHost(&ip,"192.168.2.126", PORT) < 0)
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
	SDLNet_TCP_Recv(csd, &msg, sizeof(netmsg));
	if (msg == SEED){
	    SDLNet_TCP_Recv(csd, &seed, sizeof(seed));
	}
	else{
	    cerr<< "Major fail expecting seed got garbage" <<endl;
	}
	srand(seed);
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
    unsigned int seed;
    netmsg msg = SEED;
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
    seed = time(NULL);
    
    SDLNet_TCP_Send(csd, &msg, sizeof(seed));
    SDLNet_TCP_Send(csd, &seed, sizeof(seed));
    srand(seed);
}
NetPlayer::~NetPlayer()
{
    // delete twoplayer;
}
