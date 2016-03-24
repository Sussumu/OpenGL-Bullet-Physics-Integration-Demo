#pragma once

#include "Camera.h"
#include "WindowComponent.h"
#include "Logger.h"
#include "Scenarios.h"
#include "GravityScenario.h"
#include "TestScenario.h"

#include <GL/glew.h>
#include <vector>

class Simulador
{

public:

	Simulador(int option);
	~Simulador();

	void setupScenario(int option);
	void gameLoop();

private:

	enum SimulationState
	{
		PLAY,
		EXIT
	} m_simulationState;

	// Cálculo do DeltaTime (tempo passado desde o último frame) e FPS
	float m_actualTicks, m_lastTicks, m_deltaTime;
	float m_maxFps;

	// Componentes
	WindowComponent* m_window;
	Scenario* m_scenario;
	Camera* m_camera;

	void updatePhysics(int deltaTime);
	void render();
	void eventHandler();
	void keyboardHandler(const Uint8* key);
	void mouseHandler(double currentMouseX, double currentMouseY);
	void mouseScrollHandler(double offset);
	void endProgram();
};

