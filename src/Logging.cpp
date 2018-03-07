#include "Logging.h"

HANDLE gameConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Logging::Log(char* text)
{
	SetConsoleTextAttribute(gameConsole, 11);

	SDL_Log("[%s] %s;", getTime(), text);
}

void Logging::LogInit(char* text)
{
	SetConsoleTextAttribute(gameConsole, 10);

	SDL_Log("[%s] %s;", getTime(), text);
}

void Logging::LogCrit(char* text)
{
	SetConsoleTextAttribute(gameConsole, 12);

	SDL_Log("[%s] %s;", getTime(), text);
}

char* Logging::getTime(void)
{
	time_t currTime = std::time(0);

	struct tm* info = localtime(&currTime);

	char* returnString = new char[32]();

	strftime(returnString, 32, "%d/%m/%y %T", info);

	return returnString;
}
