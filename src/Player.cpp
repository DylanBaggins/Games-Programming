#include "Player.h"
#include "TextureManager.h"
#include <math.h>

//default constructor, zeroes all vectors
Player::Player()
{
	playerPos.Zero();
	playerVelocity.Zero();
}

//overloaded constructor for accepting parameters
Player::Player(const char* path1, const char* path2, int sc)
{
	objTexture = TextureManager::loadTexture(path1);	
	mouseRet = TextureManager::loadTexture(path2);

	playerVelocity.Zero();

	srcR.w = width;
	srcR.h = height;
	srcR.x = 0;
	srcR.y = 0;

	mSrc.w = 32;
	mSrc.h = 32;
	mSrc.x = 0;
	mSrc.y = 0;

	scale = sc;

	dstR.w = width;
	dstR.h = height;
	dstR.x = ((WindowW / 2) - (dstR.w / 2));
	dstR.y = (((WindowH / 20) * 18) - (dstR.h / 3));

	playerPos.x = static_cast<float>(dstR.x);
	playerPos.y = static_cast<float>(dstR.y);
	
	playerCenter = Vector2D(playerPos.x + (dstR.w / 2), playerPos.y + (dstR.h / 2));

	mouseObj.w = 32;
	mouseObj.h = 32;
	mouseObj.x, mouseObj.y = NULL;

	stpLeft.x = -10;
	stpLeft.y = 0;
	stpLeft.w = 10;
	stpLeft.h = 640;

	stpRight.x = 960;
	stpRight.y = 0;
	stpRight.w = 10;
	stpRight.h = 640;
}

//destructor
Player::~Player()
{
	SDL_DestroyTexture(objTexture);
	SDL_DestroyTexture(mouseRet);
}

void Player::update()
{	
	fTicks = SDL_GetTicks();
	fIndex = (fTicks / 200) % 3;
	unsigned int calcX = (fWidth * fIndex);

	srcR.x = calcX;
	srcR.w = fWidth;
	srcR.h = fHeight;

	if (playerVelocity.x == 0)
	{
		srcR.y = 100;
		srcR.x = 0;
	}

	SDL_GetMouseState(&mouseObj.x, &mouseObj.y);
	mousePos = Vector2D(static_cast<float>(mouseObj.x), static_cast<float>(mouseObj.y));
	playerCenter = Vector2D(playerPos.x + (dstR.w / 2), playerPos.y + (dstR.h / 2));

	mouseObj.x = mousePos.x - (mouseObj.w / 2);
	mouseObj.y = mousePos.y - (mouseObj.h / 2);

	dstR.x = static_cast<float>(playerPos.x += (playerVelocity.x * speed));

	if (Collision::AABB(dstR, stpLeft))
	{
		playerVelocity.x = 0;
	}

	if (Collision::AABB(dstR, stpRight))
	{
		playerVelocity.x = 0;
	}
}

void Player::input()
{
	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_a:
			srcR.y = 50;
				playerVelocity.x = -1;
				Mix_PlayChannel(-1, g.Move, 0);
				Logging::Log("[A] Moving Left;");
			break;
		case SDLK_d:
			srcR.y = 0;
				playerVelocity.x = 1;
				Mix_PlayChannel(-1, g.Move, 0);
				Logging::Log("[A] Moving Right;");
			break;
		default:
			break;
		}
	}
	
	if (Game::event.type == SDL_KEYUP)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_a:
			playerVelocity.x = 0;
			break;
		case SDLK_d:
			playerVelocity.x = 0;
			break;
		default:
			break;
		}
	}
}

void Player::draw()
{	
	SDL_RenderCopy(Game::renderer, objTexture, &srcR, &dstR);
	SDL_RenderCopy(Game::renderer, mouseRet, &mSrc, &mouseObj);
	SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
}