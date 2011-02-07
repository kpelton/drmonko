/*
 * MenuWindow.h
 *
 *  Created on: Feb 6, 2011
 *      Author: kyle
 */

#ifndef MENUWINDOW_H_
#define MENUWINDOW_H_

#include "GLobject.h"
#ifdef _WIN32
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_ttf.h>
#else
#include "SDL.h"
#include "SDL_ttf.h"
#endif
#include <vector>
#include <string>
#include "types.h"

class MenuWindow: public GLobject {
public:
	MenuWindow(const int width, const int height,const string &title,TTF_Font * font);
	virtual bool render();
	virtual bool resize(){return true;};
	virtual bool loadTextures(){return true;};
	virtual ~MenuWindow();
	virtual int timerCb(){return 0;};
	void addOption(const string & option);
	bool handleEvent(SDL_Event *event);//Return true when a menu item was selected
	string getSelected(){return options[selected];};

private:
	bool handleKey(player_types::key key);
	TTF_Font * font;
	vector<string> options;
	string title;
	unsigned int selected;
	int width;
	int height;
	bool custom;


};

#endif /* MENUWINDOW_H_ */
