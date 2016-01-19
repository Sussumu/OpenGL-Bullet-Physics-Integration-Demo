#include "Scenario.h"

Scenario::Scenario()
{
}

Scenario::~Scenario()
{
}

void Scenario::setupScenario(ShaderProgram* shaderPrograms)
{
	// Será sobrescrito pelas classes derivadas
}

void Scenario::renderScenario()
{
	for each (GameObject* gameObject in objectsList)
	{
		gameObject->update();
	}
}

void Scenario::cleanScenario()
{
	for each (GameObject* gameObject in objectsList)
	{
		gameObject->clean();
	}
}
