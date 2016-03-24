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

	GLuint m_objectColorLoc, m_lightAmbient, m_lightDiffuse, m_lightSpecular, m_lightDirection, m_viewPosLoc;
	GLuint m_modelLoc, m_viewLoc, m_projLoc;

	btCollisionShape* m_shape;
	btDefaultMotionState* m_motionState;
	btRigidBody* m_rigidBody;
	btScalar m_yaw, m_pitch, m_roll;
};