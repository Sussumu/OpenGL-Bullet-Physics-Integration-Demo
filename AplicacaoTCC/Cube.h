#pragma once

#include "GameObject.h"
#include "ShaderProgram.h"

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube : public GameObject
{

public:

	Cube(ShaderProgram* shaderProgram, GLfloat size, glm::vec3 position, float mass, bool enablePhysics);
	~Cube();

	const std::string name { "Cube" };

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

	btTransform m_transform;
	float m_mass;
	btVector3 m_inertia;
	btCollisionShape* m_shape;
	btDefaultMotionState* m_motionState;
	btRigidBody* m_rigidBody;
	btScalar m_yaw, m_pitch, m_roll;
};