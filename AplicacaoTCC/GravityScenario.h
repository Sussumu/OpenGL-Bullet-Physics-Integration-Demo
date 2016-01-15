#pragma once

#include "Scenario.h"
#include "GameObject.h"
#include "Cube.h"
#include "ShaderProgram.h"
#include <vector>

class GravityScenario : public Scenario
{
public:
	GravityScenario();
	~GravityScenario();

	void setupScenario();
	//void renderScenario(ShaderProgram shaderProgram);
	//void cleanScenario();

private:
	GameObject* cube;

	std::vector<GameObject*> objectsList;
};

