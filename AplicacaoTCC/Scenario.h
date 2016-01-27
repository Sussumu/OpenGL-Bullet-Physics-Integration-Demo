#pragma once

#include "GameObject.h"
#include <vector>

class Scenario
{
public:
	Scenario();
	~Scenario();

	std::vector<GameObject*> objectsList;

	virtual void setupScenario();
	virtual void updatePhysics();
	virtual void renderScenario();
	virtual void cleanScenario();

private:
	
};

