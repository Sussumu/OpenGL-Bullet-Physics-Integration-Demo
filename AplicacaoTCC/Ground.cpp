#include "Ground.h"

Ground::Ground(ShaderProgram* shaderProgram, GLfloat* vertices, glm::vec3 position, bool enablePhysics)
{
	m_shaderProgram = shaderProgram;
	m_vertices = (GLfloat*)malloc(sizeof vertices);
	memcpy(m_vertices, vertices, sizeof(vertices));
	m_position = position;

	hasPhysics = enablePhysics;
	shape = new btStaticPlaneShape(btVector3(0, m_position.y, 0), 1);
	motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
		btVector3(btScalar(position.x), btScalar(position.y), btScalar(position.z))));
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(1, motionState, shape, btVector3(0, 0, 0));
	rigidBody = new btRigidBody(rigidBodyCI);
}

Ground::~Ground()
{
}

void Ground::setup()
{
#pragma region Draw
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
#pragma endregion
}

void Ground::updatePhysics()
{
	btTransform transform;
	rigidBody->getMotionState()->getWorldTransform(transform);

	m_position.x = transform.getOrigin().getX();
	m_position.y = transform.getOrigin().getY();
	m_position.z = transform.getOrigin().getZ();

	transform.getBasis().getEulerYPR(yaw, pitch, roll);
}

void Ground::update()
{
	m_shaderProgram->use();
	
#pragma region Rendering
	GLint modelLoc = glGetUniformLocation(m_shaderProgram->programID, "model");
	GLint viewLoc = glGetUniformLocation(m_shaderProgram->programID, "view");
	GLint projLoc = glGetUniformLocation(m_shaderProgram->programID, "projection");
	GLint objectColorLoc = glGetUniformLocation(m_shaderProgram->programID, "objectColor");
	GLint lightColorLoc = glGetUniformLocation(m_shaderProgram->programID, "lightColor");

	glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(lightColorLoc, 1.0f, 0.5f, 1.0f);

	glBindVertexArray(m_VAO);
	glm::mat4 model;
	model = glm::translate(model, m_position);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);

	m_shaderProgram->unuse();
#pragma endregion
}

void Ground::clean()
{
	delete shape;
	delete rigidBody->getMotionState();
	delete rigidBody;
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

btRigidBody* Ground::getRigidBody()
{
	return rigidBody;
}
