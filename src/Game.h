#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Logging.h"
#include <iostream>
#include "ScreenText.h"

class Game
{
private:
	
	bool shot = false;

public:

	int volume = 100;

	int tempVol;

	bool isRunning; 

	bool died = false;

	bool muted = false;

	static SDL_Window *window;

	bool fullScreen = false;

	Uint32 flags;

	SDL_Texture* splashS;
	SDL_Texture* deathS;

	Mix_Music *BGMusic = NULL;

	Mix_Chunk *shooty = NULL;
	Mix_Chunk *Move = NULL;
	Mix_Chunk *menuSelect = NULL;
	Mix_Chunk *Death = NULL;

	void init(const char* title, int xpos, int ypos, int width, int height, SDL_Joystick* cont);

	void splashScreen();

	void deathScreen();

	void eventHandler();
	
	void update();

	void render();

	void clean();

	void setRun();

	static SDL_Renderer *renderer;

	static SDL_Event event;
};

