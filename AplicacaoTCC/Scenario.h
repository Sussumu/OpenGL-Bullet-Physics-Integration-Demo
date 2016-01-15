#pragma once

class Scenario
{
public:
	Scenario();
	~Scenario();

	virtual void setupScenario();
	virtual void renderScenario();
};

