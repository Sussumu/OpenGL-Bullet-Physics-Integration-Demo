#pragma once

#include "GameObject.h"
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>

class DiffuseIluminationSource : public GameObject
{
public:
	DiffuseIluminationSource(std::vector<ShaderProgram*> shaderPrograms, GLfloat* vertices, glm::vec3 position, bool enablePhysics);
	~DiffuseIluminationSource();

	const std::string name{ "Lighting Cube" };

	void setup();
	void updatePhysics();
	void update();
	void clean();

	btRigidBody* getRigidBody();

private:
	std::vector<ShaderProgram*> m_shaderPrograms;
	GLfloat* m_vertices;
	glm::vec3 m_position;
	GLuint m_VBO, m_VAO;

	btCollisionShape* shape;
	btDefaultMotionState* motionState;
	btRigidBody* rigidBody;
	btScalar yaw, pitch, roll;
};

