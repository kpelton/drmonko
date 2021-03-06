//Copyright (c) 2011 Kyle Pelton
//See COPYING for license information
#include "splayer.h"
#include "types.h"
#include <SDL/SDL_mixer.h>
SPlayer::SPlayer(const int width, const int height, float size, float center,
		 float boardwidth, float start, float end):Player(),width(width), height(height) 
{
    this->size = size;
    this->start = start;
    this->end = end;
    keys = player_types::p1_keys;
    randengine.Seed(time(NULL));
    game = new Game(width,height,size,center,
		    boardwidth,start,end,keys);
    menu = NULL;
    paused = false;
    done=false;		

    newGame();

}


SPlayer::~SPlayer(){
    delete game;
}

bool  SPlayer::isDone() {
    return done;	
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
	Uint8 *keystate = SDL_GetKeyState(NULL);
	if (event && event->type == SDL_KEYDOWN) {
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
	    Mix_HaltMusic();
	    menu = new MenuWindow(width, height, "You Win!!", NULL);
	    menu->addOption("New Game");
	    menu->addOption("Main Menu");
	    break;

	case LOSS:
	    game->setPaused(true);
	    Mix_HaltMusic();
	    menu  = new MenuWindow(width,height,"GAME OVER",NULL);
	    menu->addOption("New Game");
	    menu->addOption("Main Menu");
	    break;

	default:
	    break;


	}

}
void SPlayer::newGame(){
    randengine.Seed(time(NULL));
    game->newGame();
}
void SPlayer::handlePauseEvent(const string & selection) {
    if (menu->getSelected() == "Resume") {
	game->setPaused(false);
	delete menu;
	Mix_FadeInMusic(Player::sound,-1, 2000);
	menu = NULL;
    } else if (menu->getSelected() == "Main Menu") {
       delete menu;
       menu = NULL;	
       done = true;
    } else if (menu->getSelected() == "New Game") {
      
	delete menu;
	Mix_FadeInMusic(Player::sound,-1, 2000);
	menu = NULL;
	newGame();
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
        Mix_HaltMusic();
       game->setPaused(true);
	
	menu = new MenuWindow(width, height, "Paused", NULL);
	menu->addOption("Resume");
	menu->addOption("New Game");
	menu->addOption("Main Menu");
	

    default:
	break;
    }
}
