#pragma once

#include "Scenario.h"
#include "GameObject.h"
#include "Camera.h"
#include "Cube.h"
#include "DiffuseIluminationSource.h"
#include "ShaderProgram.h"
#include "WindowComponent.h"
#include <glm/glm.hpp>
#include <vector>

class GravityScenario : public Scenario
{
public:
	GravityScenario();
	~GravityScenario();

	Camera* camera;

private:
	GameObject* cube;
	DiffuseIluminationSource* diffuseSource;
	ShaderProgram* m_shaderProgram;
	ShaderProgram* m_lightShaderProgram;

	std::vector<GameObject*> m_objectsList;
	std::vector<ShaderProgram*> m_shaderPrograms;

	void initShaders();
	void updateCamera();
	void renderScenario();
	void setupScenario();
	void cleanScenario();
};

