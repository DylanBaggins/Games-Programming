#include <iostream>
#include "Menu.h"

Menu::Menu()
{	
	titleText->setColor(255, 255, 255);
	playText->setColor(255, 255, 255);
	quitText->setColor(255, 255, 255);
	cntrPls->setColor(255, 255, 255);

	titleText->setText("Blue Turret Defense", 250, 100, 60);
	playText->setText("Play", 430, 300, 40);
	quitText->setText("Quit", 430, 500, 40);
	cntrPls->setText("Why no center pls", 10, 10, 20);

	playRect = {430, 300, 580, 350};
	quitRect = {430, 500, 580, 550};

	menuOptions.push_back(playText);
	menuOptions.push_back(quitText);
}


Menu::~Menu()
{
	for (auto& elements : menuOptions)
	{
		delete elements;
	}
}

void Menu::update(Game* pls)
{
	while (SDL_PollEvent(&Game::event))
	{

		if (Game::event.type == SDL_QUIT)
		{
			menuDisplay = false;
			pls->setRun();
			Logging::LogCrit("Quitting with SDL_QUIT;");
		}

		if (Game::event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (Game::event.button.button == SDL_BUTTON_LEFT)
			{
				if (menuIndex == 0)
				{
					menuDisplay = false;
					Logging::Log("[Left Click] Starting Game;");
				}
				if (menuIndex == 1)
				{
					menuDisplay = false;
					pls->setRun();
					Logging::LogCrit("[Left Click] Quitting Game;");
				}
			}
		}

		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				menuIndex = (menuIndex + 1) % menuOptions.size();
				Mix_PlayChannel(-1, g.menuSelect, 0);
				Logging::Log("[W] Menu Up;");
				break;
			case SDLK_UP:
				menuIndex = (menuIndex + 1) % menuOptions.size();
				Mix_PlayChannel(-1, g.menuSelect, 0);
				Logging::Log("[UP] Menu Up;");
				break;
			case SDLK_s:
				if ((menuIndex - 1) < 0)
				{
					menuIndex = menuOptions.size() - 1;
					Mix_PlayChannel(-1, g.menuSelect, 0);
					Logging::Log("[S] Menu Down;");
				}
				else {
					menuIndex--;
					Mix_PlayChannel(-1, g.menuSelect, 0);
					Logging::Log("[S] Menu Down;");
				}
				break;
			case SDLK_DOWN:
				if ((menuIndex - 1) < 0)
				{
					menuIndex = menuOptions.size() - 1;
					Mix_PlayChannel(-1, g.menuSelect, 0);
					Logging::Log("[DOWN] Menu Down;");
				}
				else {
					menuIndex--;
					Mix_PlayChannel(-1, g.menuSelect, 0);
					Logging::Log("[DOWN] Menu Down;");
				}
				break;
			case SDLK_RETURN:
				if (menuIndex == 0)
				{
					menuDisplay = false;
					Logging::Log("[Return] Starting Game;");
				}
				else if (menuIndex == 1)
				{
					menuDisplay = false;
					pls->setRun();
					Logging::Log("[Return] Quitting Game;");
				}
				break;
			case SDLK_ESCAPE:
				menuDisplay = false;
				pls->setRun();
				Logging::LogCrit("[Escape] Quitting Game;");
				break;
			default:
				break;
			}
		}

		SDL_GetMouseState(&mX, &mY);

		if (mX > playRect.x && mX < playRect.w && mY > playRect.y && mY < playRect.h)
		{
			menuIndex = 0;
			Mix_PlayChannel(-1, g.menuSelect, 0);
		}
		else if (mX > quitRect.x && mX < quitRect.w && mY > quitRect.y && mY < quitRect.h)
		{
			menuIndex = 1;
			Mix_PlayChannel(-1, g.menuSelect, 0);
		}
		else {

		}
	}

	for (int i = 0; i < menuOptions.size(); i++)
	{
		if (i == menuIndex)
		{
			menuOptions[i]->setColor(0, 255, 255);
		}
		else {
			menuOptions[i]->setColor(255, 255, 255);
		}
	}
}

void Menu::draw()
{
	SDL_SetRenderDrawColor(Game::renderer, 69, 38, 122, 255);
	SDL_RenderClear(Game::renderer);

	titleText->render();
	cntrPls->render();

	for (int i = 0; i < menuOptions.size(); i++)
	{
		if (i == menuIndex)
		{
			menuOptions[i]->setColor(255, 255, 0);
		}
		else {
			menuOptions[i]->setColor(255, 255, 255);
		}
		menuOptions[i]->render();
	}
	SDL_RenderPresent(Game::renderer);
}
