#pragma once

#include "GameObject.h"
#include "ShaderProgram.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL/SOIL.h>
#include <string>

class Sphere : public GameObject
{
public:
	Sphere(ShaderProgram* shaderProgram, float radius, float precision, glm::vec3 position, float mass, bool enablePhysics);
	~Sphere();

	const std::string name{ "Sphere" };

	void setup();
	void updatePhysics();
	void update();
	void clean();

	btRigidBody* getRigidBody();

private:
	float m_radius;
	float m_sectors, m_rings, m_precision;

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