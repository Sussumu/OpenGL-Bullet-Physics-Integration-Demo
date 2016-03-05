#include "Simulador.h"

Simulador::Simulador(int option)
{
	initializeSystems();
	setupScenario(option);
}

Simulador::~Simulador()
{
	endProgram();
}

// Inicializa janela
bool Simulador::initializeSystems()
{
	// Window + SDL init
	m_window->initializeWindow();

	return true;
}

// Seleciona e carrega o scenario, chamado pelo construtor
void Simulador::setupScenario(int option)
{
	switch (option)
	{
	case 1:
		m_scenario = new GravityScenario();
		break;
	}
	
}

// Loop principal do simulador
bool Simulador::gameLoop()
{
	while (m_simulationState != SimulationState::EXIT)
	{
		m_actualTicks = SDL_GetTicks();

		///////////////////////////////////////////////////
		eventHandler();
		updatePhysics();
		render();
		///////////////////////////////////////////////////

		if (m_window->wantToCalculateFps)
			m_window->calculateFPS();

		m_deltaTime = SDL_GetTicks() - m_actualTicks;

		// Frame limiter
		if (1000.0f / m_maxFps > m_deltaTime)
			SDL_Delay(1000.0f / m_maxFps - m_deltaTime);
	}

	return true;
}

// Atualiza a física em cada gameobject
void Simulador::updatePhysics()
{
	m_scenario->updatePhysics();
}

// Chama o método renderScenario() do scenario
void Simulador::render()
{
	m_scenario->renderScenario();

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
			keyboardHandler(sdlevent.key.keysym.sym);
			break;
		case SDL_MOUSEMOTION:
			mouseHandler(sdlevent.motion.x, sdlevent.motion.y);
			break;
		case SDL_MOUSEWHEEL:
			mouseScrollHandler(sdlevent.wheel.y);
			break;
		}
	}
}

// Trata o input do teclado
void Simulador::keyboardHandler(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_w:
		m_camera->ProcessKeyboard(FORWARD, m_deltaTime);
		break;
	case SDLK_a:
		m_camera->ProcessKeyboard(LEFT, m_deltaTime);
		break;
	case SDLK_s:
		m_camera->ProcessKeyboard(BACKWARD, m_deltaTime);
		break;
	case SDLK_d:
		m_camera->ProcessKeyboard(RIGHT, m_deltaTime);
		break;
	}
}

// Trata eventos do mouse (recebe a posição atual x,y e calcula as variações)
void Simulador::mouseHandler(double currentMouseX, double currentMouseY)
{
	if (m_firstMouse)
	{
		m_lastMouseX = currentMouseX;
		m_lastMouseY = currentMouseY;
		m_firstMouse = false;
	}

	GLfloat xoffset = currentMouseX - m_lastMouseX;
	GLfloat yoffset = m_lastMouseY - currentMouseY;

	m_lastMouseX = currentMouseX;
	m_lastMouseY = currentMouseY;

	m_camera->ProcessMouseMovement(xoffset, yoffset);
}

// Trata eventos do scroll do mouse
void Simulador::mouseScrollHandler(double offset)
{
	m_camera->ProcessMouseScroll(offset);
}

// Finaliza o programa em segurança
void Simulador::endProgram()
{
	SDL_DestroyWindow(m_window->getWindow());

	delete m_scenario;
	delete m_camera;
	delete m_window;

	SDL_Quit();
}