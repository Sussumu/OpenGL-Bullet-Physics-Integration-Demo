#pragma once

#include "ErrorHandler.h"
#include <GL/glew.h>
#include <SDL/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class WindowComponent
{
public:

	WindowComponent();
	~WindowComponent();
	
	bool wantToCalculateFps{ true };
	float m_maxFps{ 60.0f };

	SDL_Window* getWindow();
	bool initializeWindow();

	void calculateFPS();

private:

	SDL_Window* m_window{ nullptr };
	bool m_vsync{ false };

	float m_fps{ 0 };
	float m_frameTime{ 0 };
};