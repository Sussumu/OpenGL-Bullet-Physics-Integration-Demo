#pragma once

#include "GameObject.h"
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Ground : public GameObject
{
public:
	Ground(ShaderProgram* shaderProgram, GLfloat* vertices, glm::vec3 position, bool enablePhysics);
	~Ground();

	void setup();
	void updatePhysics();
	void update();
	void clean();

	btRigidBody* getRigidBody();

private:
	ShaderProgram* m_shaderProgram;
	GLfloat* m_vertices;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	GLuint m_VBO, m_VAO;

	btCollisionShape* shape;
	btDefaultMotionState* motionState;
	btRigidBody* rigidBody;
	btScalar yaw, pitch, roll;
};