#include "Scenario.h"

Scenario::Scenario()
{
}

Scenario::~Scenario()
{
}

void Scenario::renderScenario(ShaderProgram shaderProgram)
{
	for each (GameObject* gameObject in objectsList)
	{
		gameObject->update(shaderProgram);
	}
}

void Scenario::cleanScenario()
{
	for each (GameObject* gameObject in objectsList)
	{
		gameObject->clean();
	}
}
