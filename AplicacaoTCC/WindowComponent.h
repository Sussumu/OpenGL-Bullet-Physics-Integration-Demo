#pragma once

#include "Logger.h"
#include <GL/glew.h>
#include <SDL/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class WindowComponent
{
public:

	WindowComponent();
	~WindowComponent();
	
	bool wantToCalculateFps;
	float maxFps;

	SDL_Window* getWindow();
	void initializeWindow();

	void calculateFPS();

private:

	SDL_Window* m_window;
	bool m_vsync;

	float m_fps;
	float m_frameTime;
};