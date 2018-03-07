#include "Map.h"
#include "TextureManager.h"
#include "Game.h"

Map::Map()
{
	FullMap = TextureManager::loadTexture("content/sprites/FULLMAP.PNG");

	srcR.x = srcR.y = 0;
	srcR.w = 960;
	srcR.h = 640;

	dstR.x = dstR.y = 0;
	dstR.w = 960;
	dstR.h = 640;
}


Map::~Map()
{
	SDL_DestroyTexture(FullMap);
}

void Map::DrawMap()
{
	SDL_RenderCopy(Game::renderer, FullMap, &srcR, &dstR);
}
