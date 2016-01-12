#pragma once

#include <SDL/SDL.h>

class InputComponent
{
public:

	InputComponent();
	~InputComponent();

	void keyboardHandler(SDL_Keycode key);
};

