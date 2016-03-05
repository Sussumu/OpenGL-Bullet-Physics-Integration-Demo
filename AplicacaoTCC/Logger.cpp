#include "Logger.h"

void showMessage(std::string message)
{
	std::cout << message << std::endl;
}

// Finaliza o programa mostrando a mensagem de erro do SDL
void fatalError(std::string message)
{
	std::cout << message << std::endl;
	std::cout << SDL_GetError() << std::endl;

	SDL_Quit();
	exit(1);
}

void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	_COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hConsole, pos);
}