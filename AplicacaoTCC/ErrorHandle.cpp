#include "ErrorHandle.h"

#include <stdio.h>
#include <SDL/SDL.h>

// Finaliza o programa mostrando a mensagem de erro do SDL
void fatalError(std::string message)
{
	printf("%s\n", message);
	printf("%s\n\n", SDL_GetError());

	SDL_Quit();
	exit(1);
}