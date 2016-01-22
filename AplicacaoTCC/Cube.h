#pragma once

#include "GameObject.h"
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube : public GameObject
{
public:
	Cube(ShaderProgram* shaderProgram, GLfloat* vertices, glm::vec3* position);
	~Cube();

	void setup();
	void update();
	void clean();

private:
	ShaderProgram* m_shaderProgram;
	GLfloat* m_vertices;
	glm::vec3* m_position;
	GLuint m_texture1;
	GLuint m_texture2;
	GLuint m_VBO, m_VAO;
};

