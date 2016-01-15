#pragma once

#include "GameObject.h"
#include "ShaderProgram.h"
#include <vector>

class Scenario
{
public:
	Scenario();
	~Scenario();

	virtual void setupScenario() = 0;
	virtual void renderScenario(ShaderProgram shaderProgram);
	virtual void cleanScenario();

private:
	std::vector<GameObject*> objectsList;
};

