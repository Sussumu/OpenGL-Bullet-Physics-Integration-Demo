#pragma once

#include "Scenarios.h"
#include "Logger.h"
#include "GameObject.h"
#include "Camera.h"
#include "Cube.h"
#include "Ground.h"
#include "DirectionalLight.h"
#include "PhysicsHandler.h"
#include "ShaderProgram.h"
#include "WindowComponent.h"

#include <ctime>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include <math.h>

class GravityScenario : public Scenario
{

public:

	GravityScenario();
	~GravityScenario();
	
private:

	GameObject* cube;
	GameObject* diffuseSource;
	GameObject* ground;
	LightCaster* directionalLight;
	ShaderProgram* m_shaderProgram;

	glm::mat4 view, projection;

	PhysicsHandler* m_physicsHandler;

	std::vector<GameObject*> m_objectsList;

	void initShaders();
	void updateCamera(Camera* camera);
	void updatePhysics(float deltaTime);
	void renderScenario(Camera* camera);
	void setupScenario();
	void cleanScenario();
};

