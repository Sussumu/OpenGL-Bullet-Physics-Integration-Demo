#include "Simulador.h"
#include <iostream>

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	Simulador* simulador;
	
	// Menu
	int option = 0;
	do
	{
		std::cout << "Escolha o demo que deseja carregar:" << std::endl
				  << "1 - Gravidade" << std::endl
				  << "(ou 0 para sair)" << std::endl;
		// std::cin >> option;
		option = 1;
		if (option > 0)
		{
			simulador = new Simulador(option);
			system("cls");
			simulador->gameLoop();

			delete simulador;
		}

	} while (option != 0);
		
	return 0;
}