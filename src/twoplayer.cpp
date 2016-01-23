//Copyright (c) 2011 Kyle Pelton
//See COPYING for license information
#include "twoplayer.h"
#include "types.h"

TwoPlayer::TwoPlayer(const int width, const int height, float size, float center,
		     float boardwidth, float start, float end,
		     const int *keys,bool flip,const int players):Player(),
						width(width), height(height) {
    //start at 90 percent of the screen for title
    this->size = size;
    this->start = start;
    this->end = end;
    
    start = (width/3+25.0)+150.0;
    end = start +(size *(columns));
    
    rightgame = new Game(width,height,size,center,boardwidth,start,end,
			     player_types::p1_keys);
    
    menu = NULL;

    if (players == 2){
	leftgame = new Game(width,height,size,center,boardwidth,25,boardwidth+25,
			    player_types::p2_keys);
    }else if (players == 3){
	leftgame = new Game(width/2,height/2,size/2,center,boardwidth/2,start,end,
			     player_types::p1_keys); 
	games.push_back(leftgame);
	
	leftgame = new Game(width/2,height/2,size/2,center,boardwidth/2,start,end,
			     player_types::p1_keys); 
	games.push_back(leftgame);

    }
   

    newGame(time(NULL));
	
    this->keys = player_types::p2_keys;
    paused = false;
	
	
}


TwoPlayer::~TwoPlayer(){
    delete leftgame;
    delete rightgame;
}

void TwoPlayer::renderScene(SDL_Event *event) {
    player_types::key key;
    //Status gameStatus;
    if (menu) {
	if (menu->handleEvent(event)) {

	    handlePauseEvent(menu->getSelected());
	}

    } else {
	//All Logic hapens here
	       
	if (event && event->type == SDL_KEYDOWN) {
	    Uint8 *keystate = SDL_GetKeyState(NULL);
	    for (int i = 0; i < 6; i++) {
		//cast sdl key to own virtual key mapping
		if (keystate[keys[i]]) {
		    key = static_cast<player_types::key> (i);
		    handleKeys(key);
		    break;
		}
	    }
	}
    }
    rightcount = leftgame->getVirusCount();
    leftcount = rightgame->getVirusCount();
    if (menu){
	rightgame->renderScene(NULL);
	leftgame->renderScene(NULL);
    }else{
	rightgame->renderScene(event);
	leftgame->renderScene(event);
    }
    //gameStatus = leftgame->getStatus();

    if (menu){
	menu->render();
    }else{
	handleStatus(leftgame->getStatus());
	if(!menu)
	    handleStatus(rightgame->getStatus());
    }
	
    // if(leftcount - rightgame->getVirusCount() >1){
    //     leftgame->addPiece(leftcount - rightgame->getVirusCount());
    // }
    // if(rightcount - leftgame->getVirusCount() >1){
    //     rightgame->addPiece(rightcount - leftgame->getVirusCount());
    // }
	

}

Status TwoPlayer::handleStatus(const Status status){
    switch (status){
    case WIN:
        Mix_HaltMusic();
	rightgame->setPaused(true);
	leftgame->setPaused(true);
	menu  = new MenuWindow(width,height,"GAME OVER",NULL);
	menu->addOption("New Game");
	menu->addOption("Exit");
	return WIN;
	break;

    case LOSS:
        Mix_HaltMusic();
	rightgame->setPaused(true);
	leftgame->setPaused(true);
	menu  = new MenuWindow(width,height,"GAME OVER",NULL);
	menu->addOption("New Game");
	menu->addOption("Exit");
	return LOSS;
	break;

    default:
	break;


    }
    return LOSS;
}

void TwoPlayer::newGame(time_t seed){
    randengine.Seed(seed);
    rightgame->newGame();
    randengine.Seed(seed);
    leftgame->newGame();
}

void TwoPlayer::handlePauseEvent(const string & selection) {
    if (menu->getSelected() == "Resume") {
	rightgame->setPaused(false);
	leftgame->setPaused(false);

	delete menu;
	Mix_FadeInMusic(Player::sound,-1, 2000);
	menu = NULL;
    } else if (menu->getSelected() == "Exit") {
	delete menu;
	SDL_Quit();
	exit(0);
    } else if (menu->getSelected() == "New Game") {
	delete menu;
	menu = NULL;
	newGame(time(NULL));
	Mix_FadeInMusic(Player::sound,-1, 2000);
    }

}
void TwoPlayer::handleKeys(player_types::key key) {
    switch (key) {

    case player_types::LEFT:
	break;
    case player_types::RIGHT:
	break;
    case player_types::ROTATE:
	break;
    case player_types::DOWN:
	break;
    case player_types::EXIT:
         Mix_HaltMusic();
	rightgame->setPaused(true);
	leftgame->setPaused(true);
	menu = new MenuWindow(width, height, "Paused", NULL);
	menu->addOption("Resume");
	menu->addOption("New Game");
	menu->addOption("Exit");
	       
	rightcount = leftgame->getVirusCount();
	leftcount = rightgame->getVirusCount();
    default:
	break;
    }
}
