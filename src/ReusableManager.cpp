#include "ReusableManager.h"

using namespace std;

ReusableManager::ReusableManager()
{

}

ReusableManager::ReusableManager(float x, float y, int num)
{
	X = x;
	Y = y;
	Num = num;
}

ReusableManager::~ReusableManager()
{
	for (auto& element : bullets)
	{
		delete element; 
	}
}

void ReusableManager::addB(int x, int y)
{
	Bullet* tmpBullet = new Bullet(x, y, 20, 20);
	tmpBullet->velocity.x = 0;
	tmpBullet->velocity.y = 0;
	this->bullets.push_back(tmpBullet);
}

void ReusableManager::addE(int x, int y)
{
	Enemy* tmpEnemy = new Enemy(x, y, 32, 32);
	tmpEnemy->velocity.x = 0;
	tmpEnemy->velocity.y = 0;
	this->enemies.push_back(tmpEnemy);
}

void ReusableManager::shoot()
{
	int i = 0;
	bool notFound = true;
	while ((i < bullets.size()) && (notFound))
	{
		if (bullets[i]->velocity.y == 0 || bullets[i]->velocity.x == 0)
		{
			bullets[i]->cntr = 0;
			bullets[i]->velocity.x = aimDirNorm.x * 10;
			bullets[i]->velocity.y = aimDirNorm.y * 10;
			notFound = false;
		}
		i++;
	}
}

void ReusableManager::spawn()
{
	int i = 0;
	bool notFound = true;
	while ((i < enemies.size()) && (notFound))
	{
		if (enemies[i]->velocity.y == 0)
		{
			enemies[i]->cntr = 0;
			enemies[i]->velocity.y = 5;
			notFound = false;
		}
		i++;
	}
}

void ReusableManager::initB()
{
	for (int i = 0; i <Num; i++)
	{
		int PosX = X;
		int PosY = Y;
		addB(PosX, PosY);
	}
}

void ReusableManager::initE()
{
	for (int i = 0; i <Num; i++)
	{
		int PosX = rand() % 950 + 10;;
		int PosY = Y;
		addE(PosX, PosY);
	}
}


void ReusableManager::update(float mx, float px, float my, float py)
{
	aimDir = Vector2D(mx - px, my - py);
	one = aimDir.x * aimDir.x;
	two = aimDir.y * aimDir.y;
	three = one + two;
	four = sqrt(three);
	Length = static_cast<float>(four);
	aimDirNorm = Vector2D(aimDir.x / Length, aimDir.y / Length);

	X = px;
	Y = py;

	for (auto& element : bullets)
	{
		element->Update();

		if (element->Y <= -10 || element->Y >= 650 || element->X <= -10 || element->X >= 970) element->cntr++;
		if (element->cntr > 2)
		{
			element->cntr = 0;
			element->X = X;
			element->Y = Y;
			element->velocity.y = 0;
			element->velocity.x = 0;
		}
	}
}

void ReusableManager::update(float mx, float px, float my, float py, std::vector<Bullet*> test, SDL_Rect collRect, Game* pls)
{	
	spawnX = rand() % 10 + 1;

	if (spawnX == 5)
	{
		spawn();
	}
	
	rando = rand() % 950 + 10;

	for (auto& element : enemies)
	{
		element->Update();

		for (auto& bulls : test)
		{
			if (Collision::AABB(element->en, bulls->bull))
			{
				element->srcR.y = 32;
				element->cntr++;
				//Too much console spam when left in
				//Logging::Log("Bullet & Enemy Collision;");
			}

			if (!Collision::AABB(element->en, bulls->bull))
			{
				//Resets sprite if there is no current collision
				element->srcR.y = 0;
			}
		}

		if (Collision::AABB(element->en, collRect))
		{
			//game over
			Logging::LogCrit("Bullet & Player Collision;");
			pls->setRun();
			pls->died = true;
		}

		if (element->Y >= 650) element->cntr++;
		if (element->cntr > 2)
		{
			element->cntr = 0;
			element->X = rando;
			element->Y = -40;
			element->velocity.y = 0;
			element->srcR.y = 0;
		}
	}
}

void ReusableManager::render()
{
	for (auto& element : bullets)
	{
		if (element->velocity.y != 0 || element->velocity.x != 0)
			element->Render();
	}

	for (auto& element : enemies)
	{
		if (element->velocity.y != 0)
			element->Render();
	}
}