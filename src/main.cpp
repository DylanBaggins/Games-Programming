#define STB_TRUETYPE_IMPLEMENTATION

#include <iostream> 
#include <string>   
#include "SDL.h"
#include "Game.h"
#include "Menu.h"
#include "ScreenText.h"

//Window width and window height
#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 640

//Alias
using namespace std;
//Game G;

Game *game = nullptr;
Menu *menu = nullptr;
SDL_Joystick* controller = NULL;
int main(int argc, char *argv[])
{
	const int frameRate = 60;
	const int frameDelay = 1000 / frameRate;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	
	game->init("Blue Turret Defence, Dylan King, 16602559, Games Programming CGP2011M", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, controller);

	game->splashScreen();

	menu = new Menu();
	
	while (menu->menuDisplay)
	{
		menu->update(game);
		menu->draw();
	}

	menu->~Menu();

	while (game->isRunning)
	{
		SDL_ShowCursor(SDL_DISABLE);

		frameStart = SDL_GetTicks();

		game->update();
		game->eventHandler();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	if (!game->isRunning && game->died)
	{
		game->deathScreen();
	}

	game->clean();

	//Finally, exit
	return 0;
}

//Please don't fail me...
//I tried
//Sorry :(
