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

// Inicializa janela, shaders e câmera
bool Simulador::initializeSystems()
{
	// Window + SDL init
	m_window->initializeWindow();

	// Shaders
	initShaders();

	// Câmera
	m_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	return true;
}

// Inicializa os shaders e adiciona atributos
void Simulador::initShaders()
{
	m_shaderProgram->compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_shaderProgram->addAttribute("vertexPosition");
	m_shaderProgram->addAttribute("vertexColor");
	m_shaderProgram->linkShaders();
	
	m_lightShaderProgram->compileShaders("Shaders/lightShading.vert", "Shaders/lightShading.frag");
	//m_lightShaderProgram->addAttribute("vertexPosition");
	//m_lightShaderProgram->addAttribute("vertexColor");
	m_lightShaderProgram->linkShaders();

	m_shaderPrograms.push_back(m_shaderProgram);		// 0
	m_shaderPrograms.push_back(m_lightShaderProgram);	// 1
}

// Seleciona e carrega o scenario, chamado pelo construtor
void Simulador::setupScenario(int option)
{
	switch (option)
	{
	case 1:
		m_scenario = new GravityScenario(m_shaderPrograms);
		break;
	}
}

// Loop principal do simulador
bool Simulador::gameLoop(int scenario)
{
	while (m_simulationState != SimulationState::EXIT)
	{
		m_actualTicks = SDL_GetTicks();

		///////////////////////////////////////////////////
		eventHandler();
		updateCamera();
		render(scenario);
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

// Trata as chamadas de OpenGL
void Simulador::render(int scenario)
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// SHADER -----------------------------------------------------------------
	//m_shaderProgram->use();
	//m_lightShaderProgram->use();
	for each (auto shader in m_shaderPrograms)
	{
		shader->use();
	}

	m_scenario->renderScenario();

	// END SHADER -------------------------------------------------------------
	for each (auto shader in m_shaderPrograms)
	{
		shader->unuse();
	}

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

// Atualiza a posição da câmera
void Simulador::updateCamera()
{
	glm::mat4 view;
	view = m_camera->GetViewMatrix();
	glm::mat4 projection;
	projection = glm::perspective(m_camera->Zoom, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);

	GLint modelLoc = glGetUniformLocation(m_shaderProgram->programID, "model");
	GLint viewLoc = glGetUniformLocation(m_shaderProgram->programID, "view");
	GLint projLoc = glGetUniformLocation(m_shaderProgram->programID, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

// Finaliza o programa em segurança
void Simulador::endProgram()
{
	SDL_DestroyWindow(m_window->getWindow());

	delete m_shaderProgram;
	delete m_window;

	SDL_Quit();
}