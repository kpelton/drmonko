#include "splayer.h"
#include "types.h"

SPlayer::SPlayer(const int width, const int height, float size, float center,
		 float boardwidth, float start, float end, int argc, char **argv):Player(),
										  width(width), height(height) 
{
        this->size = size;
	this->start = start;
	this->end = end;
	keys = player_types::p1_keys;
	srand(time(NULL));
	game = new Game(width,height,size,center,
			boardwidth,start,end,argc,argv,keys);
	menu = NULL;
	paused = false;
	

}


SPlayer::~SPlayer(){
	delete game;
}

void SPlayer::renderScene(SDL_Event *event) {
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

	if (menu)
		game->renderScene(NULL);
	else
		game->renderScene(event);
	gameStatus = game->getStatus();

	if (menu)
		menu->render();
	else
	switch (gameStatus){

	case WIN:
		menu = new MenuWindow(width, height, "You Win!!", NULL);
		menu->addOption("New Game");
		menu->addOption("Exit");
		break;

	case LOSS:
		game->setPaused(true);
		menu  = new MenuWindow(width,height,"GAME OVER",NULL);
		menu->addOption("New Game");
		menu->addOption("Exit");
		break;

	default:
		break;


	}

}

void SPlayer::handlePauseEvent(const string & selection) {
	if (menu->getSelected() == "Resume") {
		game->setPaused(false);
		delete menu;
		menu = NULL;
	} else if (menu->getSelected() == "Exit") {
		SDL_Quit();
	} else if (menu->getSelected() == "New Game") {
		delete menu;
		menu = NULL;
		game->newGame();
	}

}
void SPlayer::handleKeys(player_types::key key) {
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
		game->setPaused(true);
		menu = new MenuWindow(width, height, "Paused", NULL);
		menu->addOption("Resume");
		menu->addOption("New Game");
		menu->addOption("Exit");

	default:
		break;
	}
}
