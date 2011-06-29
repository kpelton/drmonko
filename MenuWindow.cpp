/*
 * MenuWindow.cpp
 *
 *  Created on: Feb 6, 2011
 *      Author: kyle
 */

#include "MenuWindow.h"
#include "types.h"
MenuWindow::MenuWindow(const int width, const int height,const string & title,TTF_Font *font) {
    this->font = font;
    this->width = width;
    this->height = height;
    this->title = title;
    selected = 0;
    if(this->font){
	custom = true; //custom font
    }else{
	this->font = GLobject::loadFont("fonts/Ubuntu-R.ttf",45);
	custom = false;
    }

	

	
}



MenuWindow::~MenuWindow() {
    //Font should be destroyed by owner
    if(!custom)
	TTF_CloseFont(font);
}

void MenuWindow::addOption(const string & option){
    options.push_back(option);

}
string MenuWindow::getInput(const string & option){
    for(unsigned int j = 0; j<inputs.size(); j++){
	if (option == inputs[j])
	    return values[j];
    }
    return string("");
}
void MenuWindow::addInput(const string & option){
    options.push_back(option);
    inputs.push_back(string(option));
    values.push_back(string(""));
}
void MenuWindow::deleteOption(const int num){
    options.erase(options.begin() + num);

}
bool MenuWindow::handleEvent(SDL_Event *event){
    //Return true if item was selected
    player_types::key key;
    if( event && event->type == SDL_KEYDOWN){
	for(int i=0; i<player_types::NONE; i++)
	    {
		//cast sdl key to own virtual key mapping
		if(event->key.keysym.sym == player_types::p1_keys[i]){
		    key = static_cast<player_types::key>(i);
		    return handleKey(key);
		    break;
		}
	    }
			
	cerr << (SDL_GetKeyName(event->key.keysym.sym)) <<endl;
	for(unsigned int j = 0; j<inputs.size(); j++){
	    if (options[selected] == inputs[j]){
		if ((event->key.keysym.sym >= SDLK_0 && event->key.keysym.sym <= SDLK_z)||
		    string(SDL_GetKeyName(event->key.keysym.sym)) == ".")
				    
		    values[j]+=SDL_GetKeyName(event->key.keysym.sym);
				
		else if (string(SDL_GetKeyName(event->key.keysym.sym)) == "backspace")
		    values[j] = values[j].substr(0, values[j].length() - 1);
				
		else if (string(SDL_GetKeyName(event->key.keysym.sym)) == "space")
		    values[j] += " ";			 
	    }
	}
    }
    return false;
}
bool MenuWindow::handleKey(player_types::key key){
    //Switch menu selection
    switch(key){
    case player_types::ROTATE:
	if (selected >0)
	    selected--;
	else
	    selected = options.size()-1;
	break;
    case player_types::DOWN:
	if (selected < options.size()-1)
	    selected++;
	else
	    selected = 0;
	break;

    case player_types::SELECT:
	return true;
	break;
    default:

	break;
    }
    return false;
}
bool MenuWindow::render(){
    int curry = height/3;
    int spacing  = 100; //100 pixels between entries
    string curr = "";
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.0,0.0,0.0,0.8);

    glBegin(GL_QUADS); // Start drawing a quad primitive
    glVertex2f(0, 0);
    glVertex2f(width, 0);
    glVertex2f(width, height);
    glVertex2f(0,height);
    glEnd();

    glEnable(GL_TEXTURE_2D);

    glColor4f(1.0,1.0,1.0,1.0);

    GLobject::drawText(font, 255,0,255, (width/2) - (title.length()*22.5/2), curry/3,title);

    for (unsigned int i=0; i<options.size(); i++) { //loop through vector

	if(i == selected) //Set the selected alpha to correct value
	    glColor4f(1.0,1.0,1.0,1.0);
	else
	    glColor4f(1.0,1.0,1.0,0.6);
	//do the drawing
	curr = options[i];
	for (unsigned int j=0; j<inputs.size(); j++) { //loop through vector
	    if (curr == inputs[j]){
		
		curr = inputs[j] + string(":") + values[j]; 
			 
	    }
	}

	GLobject::drawText(font, 0,255,0,(width/2) - (options[i].length()*22.5/2), curry,curr);
	//add spacing for next entry
	curry+=spacing;

    }
    glDisable( GL_BLEND );
    glDisable(GL_TEXTURE_2D);
    return true;
}


