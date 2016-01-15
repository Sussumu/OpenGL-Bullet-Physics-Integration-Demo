#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GameObject.h"

class Cube : public GameObject
{
public:
	Cube(GLfloat vertices[], glm::vec3 position[]);
	~Cube();

	void setup();
	void update(ShaderProgram shaderProgram);
	void clean();

private:
	GLfloat* m_vertices;
	glm::vec3* m_position;
	GLuint m_texture1;
	GLuint m_texture2;
	GLuint m_VBO, m_VAO;
};

