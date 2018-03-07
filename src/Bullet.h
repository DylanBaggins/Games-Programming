#pragma once

#include "Game.h"
#include "Vector2D.h"
#include "Player.h"

class Bullet
{
public:
	SDL_Texture* bulletTexture;
	
	Vector2D velocity;

	SDL_Rect bull;

	int X, Y, width, height;

	int cntr;

	Bullet();

	Bullet(int x, int y, int w, int h);

	~Bullet();

	void Update();

	void Render();
};

