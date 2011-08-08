//Copyright (c) 2011 Kyle Pelton
//See COPYING for license information
#include "netgame.h"
#include "networkplayer.h"



NetTwoPlayer::NetTwoPlayer(int width,int height,float size,float center,
			   float boardwidth,float start,float end, 
			   const int *keys,bool flip,TCPsocket csd):
                           TwoPlayer(width,height,size,center,boardwidth, start,end , keys,flip)
{
    lastrow = TwoPlayer::rightgame->getRow();
    lastcol = TwoPlayer::rightgame->getCol();
    lastrot = TwoPlayer::rightgame->getRot();
    TwoPlayer::leftgame->setPaused(true);
    this->csd = csd;
    
}
void NetTwoPlayer::startGame(time_t seed){
    sent = false;
    newGame(seed);
}
void NetTwoPlayer::setCurr(const int curr){

    TwoPlayer::leftgame->addToBoard();
    cout <<"Called" <<curr <<endl;
}

Status NetTwoPlayer::getStatus(){
    return rightgame->getStatus();
}
Status NetTwoPlayer::handleStatus(const Status status){
    netmsg msg;

    switch (getStatus()){
    case LOSS:
      if (!sent){	
	cout <<"Sending lose msg"<<endl;
	msg = GAMEOVER;
	
	SDLNet_TCP_Send(csd, &msg, sizeof(msg));
        sent = true;
      }
	return LOSS;
	break;

    case WIN:
      if (!sent){
	cout <<"Sending win msg"<<endl;

	msg = NETWIN;
	SDLNet_TCP_Send(csd, &msg, sizeof(msg));
	sent = true;
      }
	return WIN;
	break;

    default:
	break;


    }
    return INPROGRESS;
}
void NetTwoPlayer::setNetRowCol(const int row, const int col,const int rot){

    TwoPlayer::leftgame->setRow(row);
    TwoPlayer::leftgame->setCol(col);
    TwoPlayer::leftgame->setRot(rot);
    
}


void NetTwoPlayer::renderScene(SDL_Event *event){
    last =  TwoPlayer::rightgame->getPiece()->getCurr();

    TwoPlayer::renderScene(event);
    TwoPlayer::leftgame->setPaused(true);
    Uint32 row  = TwoPlayer::rightgame->getRow();
    Uint32 col = TwoPlayer::rightgame->getCol();
    Uint32 rot = TwoPlayer::rightgame->getRot();
    Uint32 curr = TwoPlayer::rightgame->getPiece()->getCurr();

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

