#pragma once
#include "SDL.h"

class Collision
{
public:
	//Only one, no need to keep instantiating
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};