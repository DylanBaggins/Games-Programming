#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Player.h"
#include "ReusableManager.h"
#include "SDL_mixer.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Window* Game::window = nullptr;
SDL_Event Game::event;

Map* map;
Player* player;
ReusableManager* rMan;
ReusableManager* eMan;

//Initialise the game and pass in the title, window pos, window size and fullscreen
void Game::init(const char* title, int xpos, int ypos, int width, int height, SDL_Joystick* cont)
{
	flags = SDL_WINDOW_RESIZABLE;
	fullScreen = false;

	//Initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		//SetConsoleTextAttribute(gameConsole, 12);
		
		//Log an error
		Logging::LogCrit("An error occurred when initialising SDL.. closing..");

		//Game will not start if SDL fails
		isRunning = false;
	}
	else {
		//Log success
		Logging::LogInit("SDL initialised succesfully");

		//create the window to be used
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			Logging::LogInit("Window created succesfully");
		}

		//create the renderer
		renderer = SDL_CreateRenderer(window, -1, 0);
		// Set size of renderer to the same as window
		SDL_RenderSetLogicalSize(renderer, width, height);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer ,255, 255, 255, 255);
			Logging::LogInit("Renderer created succesfully");
		}
		if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
		{
			Logging::LogCrit("GamePad not initialised");
		}
		if (SDL_NumJoysticks() < 1)
		{
			Logging::LogCrit("GamePad not found;");
		}
		else
		{
			cont = SDL_JoystickOpen(0);
			Logging::Log("Controller connected;");
			if (cont == NULL)
			{
				Logging::Log("Controller not connected;");
			}
		}
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
			Logging::LogCrit("Sound Unavailable");
		}
		else {
			BGMusic = Mix_LoadMUS("content/sounds/10_Arpanauts.wav");
			Mix_VolumeMusic(volume);
			Move = Mix_LoadWAV("content/sounds/Move.wav");
			menuSelect = Mix_LoadWAV("content/sounds/Menu.wav");
			Death = Mix_LoadWAV("content/sounds/Death.wav");
			shooty = Mix_LoadWAV("content/sounds/Shoot.wav");
			Logging::Log("Music initialised");
			Mix_VolumeChunk(shooty, (volume / 10));
			Mix_VolumeChunk(Move, (volume / 10));
			Mix_VolumeChunk(Death, (volume / 10));
			Mix_VolumeChunk(menuSelect, (volume / 10));
		}

		//start the game
		isRunning = true;
	}

	map = new Map();

	player = new Player("content/sprites/player.png", "content/sprites/mouseRet.png", 4);

	rMan = new ReusableManager(player->playerCenter.x, player->playerCenter.y, 10);
	rMan->initB();


	eMan = new ReusableManager(rand() % 950 + 10, -20, 10);
	eMan->initE();

	Mix_PlayMusic(BGMusic, -1);
}

void Game::splashScreen()
{
	splashS = TextureManager::loadTexture("content/sprites/splashscreen.png");

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, splashS, NULL, NULL);
	SDL_RenderPresent(renderer);

	Logging::Log("Displaying spash screen");

	SDL_Delay(5000);
}

void Game::deathScreen()
{
	deathS= TextureManager::loadTexture("content/sprites/deathscreen.png");

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, deathS, NULL, NULL);
	SDL_RenderPresent(renderer);

	Logging::Log("Displaying death screen");

	SDL_Delay(1500);
}

void Game::eventHandler()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
			Logging::LogCrit("Quitting with SDL_QUIT");
		}

		if (Game::event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (!shot)
			{
				if (Game::event.button.button == SDL_BUTTON_LEFT)
				{
					rMan->shoot();
					Mix_PlayChannel(-1, shooty, 0);
					shot = true;
					Logging::Log("[Left Click Down] Firing Bullet");
				}
			}
		}

		if (Game::event.type == SDL_MOUSEBUTTONUP)
		{
			if (Game::event.button.button == SDL_BUTTON_LEFT)
			{
				shot = false;
				Logging::Log("[Left Click Up]");
			}
		}

		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				isRunning = false;
				Logging::LogCrit("[Escape] Quitting");
				break;
			case SDLK_f:
				if (fullScreen != true)
				{
					flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
					SDL_SetWindowFullscreen(window, flags);
					fullScreen = true;
					Logging::Log("[F] Fullscreen");
				}
				else {
					flags = SDL_WINDOW_RESIZABLE;
					SDL_SetWindowFullscreen(window, flags);
					fullScreen = false;
					Logging::Log("[F] Resizable");
				}
				break;
			case SDLK_EQUALS:
				if (volume < 250)
				{
					volume = volume + 10;
					Logging::Log("[Equals] volume up");
					std::cout << "Volume:" << volume << std::endl;
				}
				break;
			case SDLK_MINUS:
				if (volume > 0)
				{
					volume = volume - 10;
					Logging::Log("[Minus] volume up");
					std::cout << "Volume:" << volume << std::endl;
				}
				break;
			case SDLK_0:
				if (!muted)
				{
					tempVol = volume;
					volume = 0;
					muted = true;
					Logging::Log("[Zero] muted");
				}else if (muted)
				{
					volume = tempVol;
					muted = false;
					Logging::Log("[Zero] un-muted");
				}
				
			default:
				break;
			}
		}

		player->input();
	}
}

void Game::update()
{
	player->update();
	rMan->update(player->mousePos.x, player->playerCenter.x, player->mousePos.y, player->playerCenter.y);
	eMan->update(player->mousePos.x, player->playerCenter.x, player->mousePos.y, player->playerCenter.y, rMan->bullets, player->dstR, this);

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == 0)
	{
		Mix_VolumeMusic(volume);
		Mix_VolumeChunk(shooty, (volume / 10));
		Mix_VolumeChunk(Move, (volume / 10));
		Mix_VolumeChunk(Death, (volume / 10));
		Mix_VolumeChunk(menuSelect, (volume / 10));
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	map->DrawMap();

	rMan->render();

	eMan->render();

	player->draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_FreeChunk(shooty);
	Mix_FreeMusic(BGMusic);
	IMG_Quit();
	SDL_Quit();
	Logging::LogCrit("Game cleaned up");
	system("PAUSE");
}

void Game::setRun()
{
	isRunning = false;
}

