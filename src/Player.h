#pragma once
#include "Game.h"
#include "Vector2D.h"
#include <vector>
#include "Texturemanager.h"
#include "Collision.h"

class Player
{

private:
	int WindowW = 960;
	int	WindowH = 640;

public:
	Game g;

	SDL_Texture* objTexture;
	SDL_Texture* mouseRet;
	
	Vector2D playerPos;
	Vector2D playerVelocity;
	Vector2D playerCenter;
	Vector2D mousePos;

	SDL_Rect srcR, mSrc, dstR;
	SDL_Rect mouseObj;
	SDL_Rect stpLeft, stpRight;

	int width = 90;
	int height = 50;
	int scale = 1;
	int speed = 5;

	unsigned int fWidth = 90;
	unsigned int fHeight = 50;
	unsigned int fTicks;
	unsigned int fIndex;

	//default constructor, zeroes all vectors
	Player();
	
	//overloaded constructor for file path and scale changes
	Player(const char* path1, const char* path2, int sc);

	//destructor
	~Player();

	void update();

	void input();

	void draw();
};