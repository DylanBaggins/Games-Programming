#pragma once
#include "Game.h"

class Map
{
private:
	SDL_Rect srcR, dstR;
	SDL_Texture* FullMap;

public:
	Map();
	
	~Map();

	void DrawMap();
};

