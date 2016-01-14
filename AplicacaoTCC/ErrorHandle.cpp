#include "ErrorHandle.h"

#include <SDL/SDL.h>
#include <iostream>

// Finaliza o programa mostrando a mensagem de erro do SDL
void fatalError(std::string message)
{
	std::cout << message << std::endl;
	std::cout << SDL_GetError() << std::endl;

	SDL_Quit();
	exit(1);
}