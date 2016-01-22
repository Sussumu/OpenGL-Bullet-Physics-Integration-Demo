#pragma once

#include "Scenario.h"
#include "GameObject.h"
#include "Cube.h"
//#include "DiffuseIluminationSource.h"
#include "ShaderProgram.h"
#include <vector>

class GravityScenario : public Scenario
{
public:
	GravityScenario();
	~GravityScenario();

	void setupScenario();

private:
	GameObject* cube;
	//DiffuseIluminationSource* diffuseSource;

	std::vector<GameObject*> objectsList;
};

