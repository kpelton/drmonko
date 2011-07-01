#include "twoplayer.h"
#include "types.h"

TwoPlayer::TwoPlayer(const int width, const int height, float size, float center,
		     float boardwidth, float start, float end,
		     const int *keys,bool flip):Player(),
						width(width), height(height) {
    //start at 90 percent of the screen for title
    this->size = size;
    this->start = start;
    this->end = end;
    //add a little space on each side for the white line
    leftgame = new Game(width,height,size,center,boardwidth+25,25,boardwidth+25,
			 player_types::p2_keys);
    start = (boardwidth+25.0)+150.0;
    end = start +(size *(columns));
    rightgame = new Game(width,height,size,center,boardwidth,start,end,
			player_types::p1_keys);
    menu = NULL;
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
    Status gameStatus;
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
    gameStatus = leftgame->getStatus();

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

void TwoPlayer::handleStatus(const Status status){
    switch (status){
    case WIN:
	rightgame->setPaused(true);
	leftgame->setPaused(true);
	menu  = new MenuWindow(width,height,"GAME OVER",NULL);
	menu->addOption("New Game");
	menu->addOption("Exit");
	break;

    case LOSS:
	rightgame->setPaused(true);
	leftgame->setPaused(true);
	menu  = new MenuWindow(width,height,"GAME OVER",NULL);
	menu->addOption("New Game");
	menu->addOption("Exit");
	break;

    default:
	break;


    }
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
	menu = NULL;
    } else if (menu->getSelected() == "Exit") {
	delete menu;
	exit(0);
    } else if (menu->getSelected() == "New Game") {
	delete menu;
	menu = NULL;
	newGame(time(NULL));
		
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
