#pragma once

#include "Scenarios.h"
#include "Logger.h"
#include "GameObject.h"
#include "Camera.h"
//#include "Cube.h"
//#include "Ground.h"
//#include "DiffuseIluminationSource.h"
//#include "PhysicsHandler.h"
#include "ShaderProgram.h"
#include "WindowComponent.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <vector>

#include "Cube.h"

class TestScenario : public Scenario
{

public:
	TestScenario();
	~TestScenario();

private:

	//GameObject* cube{ nullptr };
	//GameObject* diffuseSource{ nullptr };
	//GameObject* ground{ nullptr };
	ShaderProgram* m_shaderProgram = new ShaderProgram();
	ShaderProgram* m_lightShaderProgram = new ShaderProgram();

	//PhysicsHandler* m_physicsHandler = new PhysicsHandler();

	//std::vector<GameObject*> m_objectsList;
	std::vector<ShaderProgram*> m_shaderPrograms;

	GLuint VBO, containerVAO, lightVAO;
	GLuint modelLoc, viewLoc, projLoc;
	glm::mat4 view, projection;

	GLfloat* m_vertices;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	GLuint m_VBO, m_VAO;

	void initShaders();
	void updateCamera(Camera* camera);
	void renderScenario(Camera* camera);
	void setupScenario();
	void cleanScenario();
};

