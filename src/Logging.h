#pragma once

#include "SDL.h"
#include "Game.h"
#include <windows.h>
#include <iostream>
#include <ctime>

class Logging
{
public:
	
	static void Log(char* text);

	static void LogInit(char* text);

	static void LogCrit(char* text);

	static char* getTime();
};

