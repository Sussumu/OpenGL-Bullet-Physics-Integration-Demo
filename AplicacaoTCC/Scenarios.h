#pragma once

#include "Camera.h"
#include "GameObject.h"
#include <vector>
#include <glm/glm.hpp>

class Scenario
{
public:
	Scenario();
	~Scenario();

	std::vector<GameObject*> objectsList;

	virtual void setupScenario();
	virtual void updatePhysics(int deltaTime);
	virtual void renderScenario(Camera* camera);
	virtual void cleanScenario();

};

