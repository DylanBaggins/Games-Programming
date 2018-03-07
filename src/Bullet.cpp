#include "Bullet.h"
#include "TextureManager.h"

Bullet::Bullet()
{

}

Bullet::Bullet(int x, int y, int w, int h)
{
	bulletTexture = TextureManager::loadTexture("content/sprites/bullet.png");
	
	X = x;
	Y = y;
	width = w;
	height = h;

	bull.x = X;
	bull.y = Y;
	bull.w = width;
	bull.h = height;
}

Bullet::~Bullet()
{
	SDL_DestroyTexture(bulletTexture);
}

void Bullet::Update()
{
	X = X + velocity.x;
	Y = Y + velocity.y;
}

void Bullet::Render()
{
	bull.x = X;
	bull.y = Y;
	bull.w = width;
	bull.h = height;

	SDL_RenderCopy(Game::renderer, bulletTexture, NULL, &bull);
}