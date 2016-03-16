#pragma once

#include "Scenarios.h"
#include "Logger.h"
#include "Camera.h"
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

	ShaderProgram* m_shaderProgram = new ShaderProgram();
	ShaderProgram* m_lightShaderProgram = new ShaderProgram();

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

