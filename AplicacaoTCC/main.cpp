#include "Simulador.h"
#include <iostream>

int main(int argc, char* argv[])
{
	// Habilita outros caracteres
	setlocale(LC_ALL, "");

	// Menu
	int option = 0;
	do
	{
		std::cout << "Escolha o demo que deseja carregar:" << std::endl
				  << "1 - Gravidade" << std::endl
				  << "(ou 0 para sair)" << std::endl;

		// TODO: opção é escolhida sem input do usuário no momento...
		// std::cin >> option;
		option = 1;

		if (option > 0)
		{
			Simulador* simulador = new Simulador(option);

			// TODO: funciona somente no Windows
			system("cls");

			simulador->gameLoop();

			delete simulador;
		}

	} while (option != 0);
		
	return 0;
}