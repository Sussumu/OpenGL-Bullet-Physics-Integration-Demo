#pragma once

#include "WindowComponent.h"
#include "InputComponent.h"
#include "ShaderProgram.h"
#include "Scenario.h"

class Simulador
{
public:

	Simulador(int option);
	~Simulador();

	bool initializeSystems();
	void setupScenario(int option);
	bool gameLoop(int scenario);
	void render(int scenario);
	void eventHandler();
	void endProgram();
	Scenario* m_scenario;
private:

	enum SimulationState
	{
		PLAY,
		EXIT
	} m_simulationState;

	WindowComponent* m_window { new WindowComponent() };
	InputComponent* m_input { new InputComponent() };
	ShaderProgram* m_shaderProgram { new ShaderProgram() };

	

	void initShaders();
};

