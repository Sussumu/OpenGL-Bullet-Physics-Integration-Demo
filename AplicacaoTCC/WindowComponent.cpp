#include "WindowComponent.h"
#include "ErrorHandle.h"

#include <GL/glew.h>

WindowComponent::WindowComponent()
{
}


WindowComponent::~WindowComponent()
{
}

SDL_Window* WindowComponent::getWindow()
{
	return m_window;
}

bool WindowComponent::initializeWindow()
{
	// SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fatalError("O SDL não pode ser inicializado!");
	}

	m_window = SDL_CreateWindow("Aplicação TCC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if (m_window == nullptr)
	{
		fatalError("Falha ao criar janela.");
	}

	// OpenGL
	SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
	if (glContext == NULL)
	{
		fatalError("Falha ao criar contexto OpenGL");
	}

	// Glew
	glewExperimental = GL_TRUE;
	GLenum glewInitialization = glewInit();
	if (glewInitialization != GLEW_OK)
	{
		fatalError("Glew não pode ser inicializado.");
	}

	// Setup OpenGL
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glEnable(GL_DEPTH_TEST);

	// Vsync
	if (m_vsync)
	{
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			printf("Falha ao iniciar em modo vsync.\n%s\n", SDL_GetError());
		}
	}

	printf("OPENGL VERSION %s\n", glGetString(GL_VERSION));

	return true;
}

void WindowComponent::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float previousTicks = SDL_GetTicks();
	float currentTicks;

	currentTicks = SDL_GetTicks();
	m_frameTime = currentTicks - previousTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;
	previousTicks = currentTicks;

	int count;
	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
		count = NUM_SAMPLES;

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		m_fps = 1000.0f / frameTimeAverage;
	}
	else
		m_fps = 0.0f;

	// Imprime o FPS no console
	static int frameCounter = 0;
	frameCounter++;
	if (frameCounter == 60)
	{
		printf("%.0f\n", m_fps);
		frameCounter = 0;
	}
}