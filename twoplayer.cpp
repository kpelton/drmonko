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
			     NULL,0,player_types::p2_keys);
	start = (boardwidth+25)+150;
	end = start +(size *columns);
	leftgame = new Game(width,height,size,center,boardwidth,start,end,
			    NULL,0,player_types::p1_keys);
	menu = NULL;
	this->keys = player_types::p2_keys;
	paused = false;

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
			for (int i = 0; i < 6; i++) {
				//cast sdl key to own virtual key mapping
				if (event->key.keysym.sym == keys[i]) {
					key = static_cast<player_types::key> (i);
					handleKeys(key);
					break;
				}
			}
		}
	}

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
		leftgame->newGame();
		rightgame->newGame();
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
	        leftgame->setPaused(false);
		rightgame->setPaused(false);
		menu = new MenuWindow(width, height, "Paused", NULL);
		menu->addOption("Resume");
		menu->addOption("New Game");
		menu->addOption("Exit");

	default:
		break;
	}
}
