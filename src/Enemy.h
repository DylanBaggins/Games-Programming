#pragma once

#include "Game.h"
#include "Vector2D.h"

class Enemy
{
public:
	SDL_Texture* enemyTexture;

	Vector2D velocity;

	SDL_Rect srcR, en;

	int X, Y, width, height;

	int cntr;

	unsigned int fWidth = 32;
	unsigned int fHeight = 32;
	unsigned int fTicks;
	unsigned int fIndex;

	Enemy();

	Enemy(int x, int y, int w, int h);

	~Enemy();

	void Update();

	void Render();
};

