#pragma once

#include "GameObject.h"
#include "ShaderProgram.h"
#include <vector>

class Scenario
{
public:
	Scenario();
	~Scenario();

	virtual void setupScenario(ShaderProgram* shaderPrograms);
	virtual void renderScenario();
	virtual void cleanScenario();

private:
	std::vector<GameObject*> objectsList;
	ShaderProgram* m_shaderPrograms;
};

