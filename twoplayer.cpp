#include "twoplayer.h"
#include "types.h"

TwoPlayer::TwoPlayer(const int width, const int height, float size, float center,
		float boardwidth, float start, float end, int argc, char **argv,
		     const int *keys):Player(),
	width(width), height(height) {
	//start at 90 percent of the screen for title
	this->size = size;
	this->start = start;
	this->end = end;

	//add a little space on each side for the white line
	rightgame = new Game(width,height,size,center,boardwidth+25,25,boardwidth+25,
			     0,0,player_types::p2_keys);
	start = (boardwidth+25.0)+150.0;
	end = start +(size *(columns));
	leftgame = new Game(width,height,size,center,boardwidth,start,end,
			    0,0,player_types::p1_keys);
	menu = NULL;
	this->keys = player_types::p2_keys;
	paused = false;
	newGame();

}


TwoPlayer::~TwoPlayer(){
	delete rightgame;
	delete leftgame;
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
	rightcount = rightgame->getVirusCount();
	leftcount = leftgame->getVirusCount();
	if (menu){
		leftgame->renderScene(NULL);
		rightgame->renderScene(NULL);
	}else{
		leftgame->renderScene(event);
		rightgame->renderScene(event);
	}
	gameStatus = rightgame->getStatus();

	if (menu){
		menu->render();
	}else{
		    handleStatus(rightgame->getStatus());
		    if(!menu)
			handleStatus(leftgame->getStatus());
		}
	
	if(leftcount - leftgame->getVirusCount() >1){
	    rightgame->addPiece(leftcount - leftgame->getVirusCount());
	}
	if(rightcount - rightgame->getVirusCount() >1){
	    leftgame->addPiece(rightcount - rightgame->getVirusCount());
	}
	

}

void TwoPlayer::handleStatus(const Status status){
    switch (status){
	case WIN:
	        leftgame->setPaused(true);
		rightgame->setPaused(true);
		menu  = new MenuWindow(width,height,"GAME OVER",NULL);
		menu->addOption("New Game");
		menu->addOption("Exit");
	        break;

	case LOSS:
		leftgame->setPaused(true);
		rightgame->setPaused(true);
		menu  = new MenuWindow(width,height,"GAME OVER",NULL);
		menu->addOption("New Game");
		menu->addOption("Exit");
		break;

	default:
		break;


    }
}

void TwoPlayer::newGame(){
    time_t seed;
    seed = time(NULL);
    srand(seed);
    leftgame->newGame();
    srand(seed);
    rightgame->newGame();
}

void TwoPlayer::handlePauseEvent(const string & selection) {
	if (menu->getSelected() == "Resume") {
		leftgame->setPaused(false);
		rightgame->setPaused(false);
		delete menu;
		menu = NULL;
	} else if (menu->getSelected() == "Exit") {
		SDL_Quit();
	} else if (menu->getSelected() == "New Game") {
		delete menu;
		menu = NULL;
		newGame();
		
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
	        leftgame->setPaused(true);
		rightgame->setPaused(true);
		menu = new MenuWindow(width, height, "Paused", NULL);
		menu->addOption("Resume");
		menu->addOption("New Game");
		menu->addOption("Exit");
		rightcount = rightgame->getVirusCount();
		leftcount = leftgame->getVirusCount();
	default:
		break;
	}
}
