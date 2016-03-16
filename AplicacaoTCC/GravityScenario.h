#pragma once

#include "Scenarios.h"
#include "Logger.h"
#include "GameObject.h"
#include "Camera.h"
#include "Cube.h"
#include "Ground.h"
#include "DiffuseIluminationSource.h"
#include "PhysicsHandler.h"
#include "ShaderProgram.h"
#include "WindowComponent.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

class GravityScenario : public Scenario
{
public:
	GravityScenario();
	~GravityScenario();
	
private:

	GameObject* cube { nullptr };
	GameObject* diffuseSource { nullptr };
	GameObject* ground { nullptr };
	ShaderProgram* m_shaderProgram = new ShaderProgram();
	ShaderProgram* m_lightShaderProgram = new ShaderProgram();

	glm::mat4 view, projection;

	PhysicsHandler* m_physicsHandler = new PhysicsHandler();

	std::vector<GameObject*> m_objectsList;

	void initShaders();
	void updateCamera(Camera* camera);
	void updatePhysics(int deltaTime);
	void renderScenario(Camera* camera);
	void setupScenario();
	void cleanScenario();
};

