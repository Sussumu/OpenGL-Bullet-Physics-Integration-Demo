#pragma once

#include "Scenario.h"
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

	Camera* camera;

private:
	GameObject* cube;
	GameObject* diffuseSource;
	GameObject* ground;
	ShaderProgram* m_shaderProgram;
	ShaderProgram* m_lightShaderProgram;

	PhysicsHandler* m_physicsHandler;

	std::vector<GameObject*> m_objectsList;
	std::vector<ShaderProgram*> m_shaderPrograms;

	void initShaders();
	void updateCamera();
	void renderScenario();
	void setupScenario();
	void cleanScenario();
};

