#pragma once
//#define STB_TRUETYPE_IMPLEMENTATION
#include "ScreenText.h"
#include "Game.h"
#include <vector>

class Menu
{
public:

	std::vector<ScreenText*>menuOptions;

	ScreenText* titleText = new ScreenText(Game::window, "../content/font/Roboto.ttf");
	ScreenText* playText = new ScreenText(Game::window, "../content/font/Roboto.ttf");
	ScreenText* quitText = new ScreenText(Game::window, "../content/font/Roboto.ttf");
	ScreenText* cntrPls = new ScreenText(Game::window, "../content/font/Roboto.ttf");

	SDL_Rect playRect, quitRect;

	Game g;
	
	int menuIndex;

	int mX, mY;

	bool menuDisplay = true;

	Menu();

	~Menu();

	void update(Game* pls);

	void draw();
};

