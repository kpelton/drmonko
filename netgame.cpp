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


void NetTwoPlayer::setNetRowCol(const int row, const int col,const int rot){

    TwoPlayer::rightgame->setRow(row);
    TwoPlayer::rightgame->setCol(col);
    TwoPlayer::rightgame->setRot(rot);
    TwoPlayer::rightgame->addToBoard();
}

void NetTwoPlayer::renderScene(SDL_Event *event){
    TwoPlayer::renderScene(event);
    Uint32 row  = TwoPlayer::leftgame->getRow();
    Uint32 col = TwoPlayer::leftgame->getCol();
    Uint32 rot = TwoPlayer::leftgame->getRot();
  

    netmsg msg = UPDATE; //update
    Uint32 rowcol = col | (row << 8) ;
    rowcol |= (rot <<16);
    
    
    if ((row != lastrow) || col != lastcol || lastrot != rot) //update send to other player
	{
	  
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

    TwoPlayer::handlePauseEvent(selection);
}

