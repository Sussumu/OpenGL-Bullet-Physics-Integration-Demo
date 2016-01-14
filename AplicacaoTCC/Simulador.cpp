#include "Simulador.h"
#include "ErrorHandle.h"
#include "GravityScenario.h"

#include <GL/glew.h>

Simulador::Simulador(int option)
{
	initializeSystems();
	setupScenario(option);
}


Simulador::~Simulador()
{
	endProgram();
}

// Inicializa o sistema
bool Simulador::initializeSystems()
{
	// Window + SDL init
	m_window->initializeWindow();

	// Shaders
	initShaders();

	return true;
}

// Inicializa os shaders e adiciona atributos
void Simulador::initShaders()
{
	m_shaderProgram->compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_shaderProgram->addAttribute("vertexPosition");
	m_shaderProgram->addAttribute("vertexColor");
	m_shaderProgram->linkShaders();
}

void Simulador::setupScenario(int option)
{
	switch (option)
	{
	case 1:
		m_scenario = new GravityScenario();
		m_scenario->setupScenario();
		break;
	}
}

// Loop principal do simulador
bool Simulador::gameLoop(int scenario)
{
	float actualTicks = 0, passedTicks = 0;
	float maxFps = 60.0f;

	while (m_simulationState != SimulationState::EXIT)
	{
		actualTicks = SDL_GetTicks();

		///////////////////////////////////////////////////
		eventHandler();
		render(scenario);
		///////////////////////////////////////////////////

		if (m_window->wantToCalculateFps)
			m_window->calculateFPS();

		passedTicks = SDL_GetTicks() - actualTicks;

		// Frame limiter
		if (1000.0f / maxFps > passedTicks)
			SDL_Delay(1000.0f / maxFps - passedTicks);
	}

	return true;
}

// Trata as chamadas de OpenGL
void Simulador::render(int scenario)
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// SHADER -----------------------------------------------------------------
	m_shaderProgram->use();

	//
	//
	//

	// END SHADER -------------------------------------------------------------
	m_shaderProgram->unuse();

	SDL_GL_SwapWindow(m_window->getWindow());
}

// Trata todos os eventos do sistema
void Simulador::eventHandler()
{
	SDL_Event sdlevent;

	while (SDL_PollEvent(&sdlevent) != 0)
	{
		switch (sdlevent.type)
		{
		case SDL_QUIT:
			m_simulationState = SimulationState::EXIT;
			break;
		case SDL_KEYDOWN:
			m_input->keyboardHandler(sdlevent.key.keysym.sym);
			break;
		}
	}
}

// Finaliza o programa em segurança
void Simulador::endProgram()
{
	SDL_DestroyWindow(m_window->getWindow());

	delete m_input;
	delete m_shaderProgram;
	delete m_window;

	SDL_Quit();
}