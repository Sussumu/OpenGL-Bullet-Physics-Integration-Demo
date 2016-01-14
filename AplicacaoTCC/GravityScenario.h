#pragma once

#include "Scenario.h"

class GravityScenario : public Scenario
{
public:
	GravityScenario();
	~GravityScenario();

	void setupScenario();
	void renderScenario();
};

