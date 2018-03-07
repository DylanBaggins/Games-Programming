#pragma once

#include "Game.h"

//Load and draw textures without the repetition
class TextureManager
{
public:

	//Creteas a surface and then creates a texture form the surface before freeing the surface
	static SDL_Texture* loadTexture(const char* fileName);

};

