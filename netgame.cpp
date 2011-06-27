#include "netgame.h"
#include "networkplayer.h"



NetTwoPlayer::NetTwoPlayer(int width,int height,float size,float center,
	      float boardwidth,float start,float end, int argc,
			   char **argv , const int *keys,bool flip,TCPsocket csd):
              TwoPlayer(width,height,size,center,boardwidth, start,end, argc,argv , keys,flip)
{
    lastrow = TwoPlayer::leftgame->getRow();
    lastcol = TwoPlayer::leftgame->getCol();
    lastrot = TwoPlayer::leftgame->getRot();
    TwoPlayer::rightgame->setPaused(true);
    this->csd = csd;
    
}
void NetTwoPlayer::startGame(time_t seed){
    newGame(seed);
}
void NetTwoPlayer::setCurr(const int curr){

    TwoPlayer::rightgame->addToBoard();
    TwoPlayer::rightgame->getPiece()->setCurr(curr);
    
    cout <<"Called" <<curr <<endl;
}

void NetTwoPlayer::handleStatus(const Status status){
    netmsg msg;
    time_t nseed;
    switch (status){
    case LOSS:
	msg = GAMEOVER;
	SDLNet_TCP_Send(csd, &msg, sizeof(msg));

	break;

	case WIN:
		// leftgame->setPaused(true);
		// rightgame->setPaused(true);
		// menu  = new MenuWindow(width,height,"GAME OVER",NULL);
		// menu->addOption("New Game");
		// menu->addOption("Exit");
		break;

	default:
		break;


    }
}
void NetTwoPlayer::setNetRowCol(const int row, const int col,const int rot){

    TwoPlayer::rightgame->setRow(row);
    TwoPlayer::rightgame->setCol(col);
    TwoPlayer::rightgame->setRot(rot);
    
}

void NetTwoPlayer::renderScene(SDL_Event *event){
    last =  TwoPlayer::leftgame->getPiece()->getCurr();

    TwoPlayer::renderScene(event);
     TwoPlayer::rightgame->setPaused(true);
    Uint32 row  = TwoPlayer::leftgame->getRow();
    Uint32 col = TwoPlayer::leftgame->getCol();
    Uint32 rot = TwoPlayer::leftgame->getRot();
    Uint32 curr = TwoPlayer::leftgame->getPiece()->getCurr();

    netmsg msg;
    Uint32 rowcol = col | (row << 8) ;
    rowcol |= (rot <<16);
    
    if (curr != last){

	msg = NEWPIECE;
	
	SDLNet_TCP_Send(csd,&msg,sizeof(netmsg));
	SDLNet_TCP_Send(csd,&curr,sizeof(Uint32)); 

 
	//new piece send newpiece command
	cout << "NewPiece!"<< curr <<endl;
    }
    if (row != lastrow || col != lastcol || lastrot != rot) //update send to other player
	{
	    msg = UPDATE;
	    SDLNet_TCP_Send(csd,&msg,sizeof(netmsg));
	    SDLNet_TCP_Send(csd,&rowcol,sizeof(Uint32)); 
	}
    


    lastrow = row;
    lastcol = col;
    lastrot = rot;
    
   

};

void NetTwoPlayer::handleKeys(player_types::key key){

    //TwoPlayer::handleKeys(key);
    
}
void NetTwoPlayer::handlePauseEvent(const string & selection){

    //TwoPlayer::handlePauseEvent(selection);
}

