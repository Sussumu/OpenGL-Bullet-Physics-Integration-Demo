#include "Simulador.h"
#include <iostream>

int main(int argc, char* argv[])
{
	Simulador* simulador;
	
	// Menu
	int option = 0;
	do
	{
		std::cout << "Escolha o demo que deseja carregar:" << std::endl
				  << "(ou 0 para sair)" << std::endl;
		std::cin >> option;

		if (option > 0)
		{
			simulador = new Simulador(option);
			simulador->gameLoop(option);

			delete simulador;
		}

	} while (option != 0);
		
	return 0;
}