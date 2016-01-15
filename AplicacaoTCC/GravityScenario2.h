#pragma once

#include "Scenario.h"

class GravityScenario : Scenario
{
public:
	GravityScenario();
	~GravityScenario();

	virtual void setupScenario() override;
	virtual void renderScenario() override;
};

