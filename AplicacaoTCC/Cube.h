#pragma once

#include "Camera.h"
#include "Simulador.h"
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
	Cube(ShaderProgram* shaderProgram, GLfloat* vertices, glm::vec3 position, float mass, bool enablePhysics);
	~Cube();

	const std::string name { "Cube" };

	void setup();
	void updatePhysics();
	void update(glm::vec3 viewPosition, glm::mat4 view, glm::mat4 projection, LightCaster* lightCaster);
	//void update(Camera* camera);
	void clean();

	btRigidBody* getRigidBody();

private:
	ShaderProgram* m_shaderProgram;
	GLfloat* m_vertices;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	GLuint m_VBO, m_VAO;

	float m_mass;
	btVector3 m_inertia;
	btCollisionShape* shape;
	btDefaultMotionState* motionState;
	btRigidBody* rigidBody;
	btScalar yaw, pitch, roll;
};