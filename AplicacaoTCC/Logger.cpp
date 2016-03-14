#include "Logger.h"

void showMessage(std::string message)
{
	std::cout << message;
	gotoxy(0, 0);
}

// Finaliza o programa mostrando a mensagem de erro do SDL
void fatalError(std::string message)
{
	gotoxy(0, 5);
	std::cout << message << std::endl;
	std::cout << SDL_GetError() << std::endl;

	SDL_Quit();
	std::string temp;
	std::cin >> temp;
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