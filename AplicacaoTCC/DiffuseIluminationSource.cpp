#include "DiffuseIluminationSource.h"

DiffuseIluminationSource::DiffuseIluminationSource(std::vector<ShaderProgram*> shaderPrograms, GLfloat* vertices, glm::vec3 position, bool enablePhysics)
{
	m_shaderPrograms = shaderPrograms;
	m_vertices = (GLfloat*)malloc(sizeof vertices);
	memcpy(m_vertices, vertices, sizeof(vertices));
	m_position = position;

	hasPhysics = enablePhysics;
	shape = new btBoxShape(btVector3(1, 1, 1));
	motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
		btVector3(btScalar(position.x), btScalar(position.y), btScalar(position.z))));
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(1, motionState, shape, btVector3(0, 0, 0));
	rigidBody = new btRigidBody(rigidBodyCI);
}

DiffuseIluminationSource::~DiffuseIluminationSource()
{
}

void DiffuseIluminationSource::setup()
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
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);

	glBindVertexArray(0);
#pragma endregion
}

void DiffuseIluminationSource::updatePhysics()
{
	btTransform transform;
	rigidBody->getMotionState()->getWorldTransform(transform);

	m_position.x = transform.getOrigin().getX();
	m_position.y = transform.getOrigin().getY();
	m_position.z = transform.getOrigin().getZ();

	transform.getBasis().getEulerYPR(yaw, pitch, roll);
}

void DiffuseIluminationSource::update()
{
	m_shaderPrograms.at(1)->use();
	
#pragma region Lighting
	glm::vec3 lightPos = m_position;
	GLint objectColorLoc = glGetUniformLocation(m_shaderPrograms.at(1)->programID, "objectColor");
	GLint lightColorLoc = glGetUniformLocation(m_shaderPrograms.at(1)->programID, "lightColor");
	GLint lightPosLoc = glGetUniformLocation(m_shaderPrograms.at(1)->programID, "lightPos");
	glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
#pragma endregion

	GLint modelLoc = glGetUniformLocation(m_shaderPrograms.at(1)->programID, "model");
	GLint viewLoc = glGetUniformLocation(m_shaderPrograms.at(1)->programID, "view");
	GLint projLoc = glGetUniformLocation(m_shaderPrograms.at(1)->programID, "projection");

	glm::mat4 model;
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
	model = glm::mat4();
	model = glm::translate(model, lightPos);
	model = glm::rotate(model, yaw, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, pitch, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, roll, glm::vec3(1.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.2f)); 
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	m_shaderPrograms.at(1)->unuse();
}

void DiffuseIluminationSource::clean()
{
	delete shape;
	delete rigidBody->getMotionState();
	delete rigidBody;
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

btRigidBody* DiffuseIluminationSource::getRigidBody()
{
	return nullptr;
}
