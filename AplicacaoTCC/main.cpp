#include "Simulador.h"
#include <Windows.h>

int main(int argc, char* argv[])
{
	Simulador* simulador{ new Simulador() };
	
	simulador->initializeSystems();

	simulador->gameLoop();

	Sleep(1000);

	delete simulador;

	return 0;
}