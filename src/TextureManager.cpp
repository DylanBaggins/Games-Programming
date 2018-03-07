#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* fileName)
{	
	//creates a surface with the file passed in
	SDL_Surface* tempSurface = IMG_Load(fileName);
	//creates a texture from the surface
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	//frees up the surface now that it is no longer needed
	SDL_FreeSurface(tempSurface);

	//returns the texture for it to be used
	return tex;
}
