#pragma once

#include "GameObject.h"
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Ground : public GameObject
{
public:
	Ground(ShaderProgram* shaderProgram, GLfloat size, glm::vec3 position, bool enablePhysics);
	~Ground();

	const std::string name{ "Ground" };

	void setup();
	void updatePhysics();
	void update(glm::vec3 viewPosition, glm::mat4 view, glm::mat4 projection, LightCaster* lightCaster);
	void clean();

	btRigidBody* getRigidBody();

private:
	ShaderProgram* m_shaderProgram;
	GLfloat m_side;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	GLuint m_VBO, m_VAO;

	btCollisionShape* shape;
	btDefaultMotionState* motionState;
	btRigidBody* rigidBody;
	btScalar yaw, pitch, roll;
};