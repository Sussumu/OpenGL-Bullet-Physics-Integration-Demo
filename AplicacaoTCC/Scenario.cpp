#include "Scenario.h"
#include "Logger.h"

Scenario::Scenario()
{
}

Scenario::~Scenario()
{
}

void Scenario::setupScenario()
{
	for each (GameObject* gameObject in objectsList)
	{
		gameObject->setup();
	}
}

void Scenario::updatePhysics()
{
	for each (GameObject* gameObject in objectsList)
	{
		gameObject->updatePhysics();
	}
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
