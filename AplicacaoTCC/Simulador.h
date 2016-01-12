#pragma once

#include "WindowComponent.h"
#include "InputComponent.h"
#include "ShaderProgram.h"

class Simulador
{
public:

	Simulador();
	~Simulador();

	bool initializeSystems();
	bool gameLoop();
	void render();
	void eventHandler();
	void endProgram();

private:

	enum SimulationState
	{
		PLAY,
		EXIT
	} m_simulationState;

	WindowComponent* m_window{ new WindowComponent() };
	InputComponent* m_input{ new InputComponent() };
	ShaderProgram* m_shaderProgram{ new ShaderProgram() };

	void initShaders();
};

