#pragma once

#include "ShaderProgram.h"

class GameObject
{
public:

	GameObject();
	~GameObject();

	virtual void setup() = 0;
	virtual void update(ShaderProgram shaderProgram) = 0;
	virtual void clean() = 0;

private:


};

