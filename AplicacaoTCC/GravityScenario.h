#pragma once

#include "Scenario.h"
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

	Camera* camera { nullptr };

private:
	GameObject* cube { nullptr };
	GameObject* diffuseSource { nullptr };
	GameObject* ground { nullptr };
	ShaderProgram* m_shaderProgram = new ShaderProgram();
	ShaderProgram* m_lightShaderProgram = new ShaderProgram();

	PhysicsHandler* m_physicsHandler = new PhysicsHandler();

	std::vector<GameObject*> m_objectsList;
	std::vector<ShaderProgram*> m_shaderPrograms;

	void initShaders();
	void updateCamera();
	void renderScenario();
	void setupScenario();
	void cleanScenario();
};

