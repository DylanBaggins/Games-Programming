#include "Enemy.h"
#include "TextureManager.h"

Enemy::Enemy()
{

}

Enemy::Enemy(int x, int y, int w, int h)
{
	enemyTexture = TextureManager::loadTexture("content/sprites/enemy.png");

	X = x;
	Y = y;
	width = w;
	height = h;

	srcR.x = 0;
	srcR.y = 0;
	srcR.w = fWidth;
	srcR.h = fHeight;

	en.x = X;
	en.y = Y;
	en.w = width * 1.5;
	en.h = height * 1.5;
}

Enemy::~Enemy()
{
	SDL_DestroyTexture(enemyTexture);
}

void Enemy::Update()
{
	fTicks = SDL_GetTicks();
	fIndex = (fTicks / 200) % 3;
	unsigned int calcX = (fWidth * fIndex);

	srcR.x = calcX;
	srcR.w = fWidth;
	srcR.h = fHeight;

	X = X + velocity.x;
	Y = Y + velocity.y;
}

void Enemy::Render()
{
	en.x = X;
	en.y = Y;
	en.w = width * 1.5;
	en.h = height * 1.5;

	SDL_RenderCopy(Game::renderer, enemyTexture, &srcR, &en);
}