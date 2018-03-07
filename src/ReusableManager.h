#pragma once

#include "Game.h"
#include "Vector2D.h"
#include "Bullet.h"
#include "Collision.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class ReusableManager
{
public:
	
	Vector2D aimDir;
	Vector2D aimDirNorm;

	Player p;
	Game g;

	float Length;
	double one;
	double two;
	double three;
	double four;

	std::vector<Bullet*>bullets;
	std::vector<Enemy*>enemies;

	int X, Y, Num;

	int spawnX;
	int rando;

	unsigned int fTicks;
	unsigned int fIndex;

	ReusableManager();

	ReusableManager(float x, float y, int num);

	~ReusableManager();

	void addB(int x, int y);
	
	void addE(int x, int y);

	void shoot();

	void spawn();

	void initB();

	void initE();

	void update(float mx, float px, float my, float py);

	void update(float mx, float px, float my, float py, std::vector<Bullet*> test, SDL_Rect collRect, Game* pls);

	void render();

};