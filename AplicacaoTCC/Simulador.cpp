#include "Simulador.h"

Simulador::Simulador(int option)
{
	initializeSystems();
	m_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
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
		//m_scenario = new TestScenario();
		break;
	}
}

// Loop principal do simulador
bool Simulador::gameLoop()
{
	SDL_WarpMouseInWindow(m_window->getWindow(), 400, 300);
	while (m_simulationState != SimulationState::EXIT)
	{
		m_actualTicks = SDL_GetTicks();
		m_deltaTime = m_actualTicks - m_lastTicks;

		///////////////////////////////////////////////////
		eventHandler();
		updatePhysics(m_deltaTime);
		render();
		///////////////////////////////////////////////////

		if (m_window->wantToCalculateFps)
			m_window->calculateFPS();

		m_lastTicks = SDL_GetTicks();

		// Frame limiter
		if (1000.0f / m_maxFps > m_deltaTime)
			SDL_Delay(1000.0f / m_maxFps - m_deltaTime);
	}

	return true;
}

// Atualiza a física em cada gameobject
void Simulador::updatePhysics(int deltaTime)
{
	m_scenario->updatePhysics(deltaTime);
}

// Chama o método renderScenario() do scenario
void Simulador::render()
{
	m_scenario->renderScenario(m_camera);

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
		case SDL_MOUSEMOTION:
			mouseHandler(sdlevent.motion.xrel, sdlevent.motion.yrel);
			break;
		case SDL_MOUSEWHEEL:
			mouseScrollHandler(sdlevent.wheel.y);
			break;
		}
	}
	// Trata eventos do teclado
	const Uint8* key = SDL_GetKeyboardState(NULL);
	keyboardHandler(key);
}

// Trata o input do teclado
void Simulador::keyboardHandler(const Uint8* key)
{
	if (key[SDL_SCANCODE_W])
		m_camera->ProcessKeyboard(FORWARD, m_deltaTime);
	if (key[SDL_SCANCODE_A])
		m_camera->ProcessKeyboard(LEFT, m_deltaTime);
	if (key[SDL_SCANCODE_S])
		m_camera->ProcessKeyboard(BACKWARD, m_deltaTime);
	if (key[SDL_SCANCODE_D])
		m_camera->ProcessKeyboard(RIGHT, m_deltaTime);
	if (key[SDL_SCANCODE_ESCAPE])
		endProgram();
}

// Trata eventos do mouse (recebe a posição atual x,y e calcula as variações)
void Simulador::mouseHandler(double currentMouseX, double currentMouseY)
{
	m_camera->ProcessMouseMovement(currentMouseX, -currentMouseY);
	//gotoxy(0, 13);
	//showMessage("Mouse offset     X " + std::to_string(xoffset));
	//gotoxy(0, 14);
	//showMessage("Mouse offset     Y " + std::to_string(yoffset));
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