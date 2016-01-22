#pragma once

#include "GameObject.h"
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class DiffuseIluminationSource : public GameObject
{
public:
	DiffuseIluminationSource(std::vector<ShaderProgram*> shaderPrograms, GLfloat* vertices, glm::vec3* position);
	~DiffuseIluminationSource();

	void setup();
	void update();
	void clean();

private:
	std::vector<ShaderProgram*> m_shaderPrograms;
	GLfloat* m_vertices;
	glm::vec3* m_position;
	GLuint m_VBO, m_VAO;
};

