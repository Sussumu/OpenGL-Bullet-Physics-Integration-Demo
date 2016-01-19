#pragma once

#include "Scenario.h"
#include "GameObject.h"
#include "Cube.h"
#include "DiffuseIluminationSource.h"
#include "ShaderProgram.h"
#include <vector>

class GravityScenario : public Scenario
{
public:
	GravityScenario(std::vector<ShaderProgram*> shaderPrograms);
	~GravityScenario();

	void setupScenario(std::vector<ShaderProgram*> shaderPrograms);

private:
	GameObject* cube;
	DiffuseIluminationSource* diffuseSource;

	std::vector<GameObject*> objectsList;
};

