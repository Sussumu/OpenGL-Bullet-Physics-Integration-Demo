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
		btVector3(btScalar(m_position.x), btScalar(m_position.y), btScalar(m_position.z))));
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(0, motionState, shape, btVector3(0, 0, 0));
	rigidBody = new btRigidBody(rigidBodyCI);
}

Ground::~Ground()
{
}

void Ground::setup()
{
	GLfloat vertices[] = {
		-10.0f, -10.0f, -10.0f,   0.0f, 0.0f, -1.0f,
		 10.0f, -10.0f, -10.0f,   0.0f, 0.0f, -1.0f,
		 10.0f,  10.0f, -10.0f,   0.0f, 0.0f, -1.0f,
		 10.0f,  10.0f, -10.0f,   0.0f, 0.0f, -1.0f,
		-10.0f,  10.0f, -10.0f,   0.0f, 0.0f, -1.0f,
		-10.0f, -10.0f, -10.0f,   0.0f, 0.0f, -1.0f,

		-10.0f, -10.0f,  10.0f,   0.0f, 0.0f,  1.0f,
		 10.0f, -10.0f,  10.0f,   0.0f, 0.0f,  1.0f,
		 10.0f,  10.0f,  10.0f,   0.0f, 0.0f,  1.0f,
		 10.0f,  10.0f,  10.0f,   0.0f, 0.0f,  1.0f,
		-10.0f,  10.0f,  10.0f,   0.0f, 0.0f,  1.0f,
		-10.0f, -10.0f,  10.0f,   0.0f, 0.0f,  1.0f,

		-10.0f,  10.0f,  10.0f,  -1.0f, 0.0f,  0.0f,
		-10.0f,  10.0f, -10.0f,  -1.0f, 0.0f,  0.0f,
		-10.0f, -10.0f, -10.0f,  -1.0f, 0.0f,  0.0f,
		-10.0f, -10.0f, -10.0f,  -1.0f, 0.0f,  0.0f,
		-10.0f, -10.0f,  10.0f,  -1.0f, 0.0f,  0.0f,
		-10.0f,  10.0f,  10.0f,  -1.0f, 0.0f,  0.0f,

		 10.0f,  10.0f,  10.0f,   1.0f, 0.0f,  0.0f,
		 10.0f,  10.0f, -10.0f,   1.0f, 0.0f,  0.0f,
		 10.0f, -10.0f, -10.0f,   1.0f, 0.0f,  0.0f,
		 10.0f, -10.0f, -10.0f,   1.0f, 0.0f,  0.0f,
		 10.0f, -10.0f,  10.0f,   1.0f, 0.0f,  0.0f,
		 10.0f,  10.0f,  10.0f,   1.0f, 0.0f,  0.0f,

		-10.0f, -10.0f, -10.0f,   0.0f, 1.0f,  0.0f,
		 10.0f, -10.0f, -10.0f,   0.0f, 1.0f,  0.0f,
		 10.0f, -10.0f,  10.0f,   0.0f, 1.0f,  0.0f,
		 10.0f, -10.0f,  10.0f,   0.0f, 1.0f,  0.0f,
		-10.0f, -10.0f,  10.0f,   0.0f, 1.0f,  0.0f,
		-10.0f, -10.0f, -10.0f,   0.0f, 1.0f,  0.0f,

		-10.0f,  10.0f, -10.0f,   0.0f, 1.0f,  0.0f,
		 10.0f,  10.0f, -10.0f,   0.0f, 1.0f,  0.0f,
		 10.0f,  10.0f,  10.0f,   0.0f, 1.0f,  0.0f,
		 10.0f,  10.0f,  10.0f,   0.0f, 1.0f,  0.0f,
		-10.0f,  10.0f,  10.0f,   0.0f, 1.0f,  0.0f,
		-10.0f,  10.0f, -10.0f,   0.0f, 1.0f,  0.0f
	};

#pragma region Draw
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
}

void Ground::update(glm::vec3 viewPosition, glm::mat4 view, glm::mat4 projection, LightCaster* lightCaster)
{
	m_shaderProgram->use();
	
#pragma region Rendering
	GLint objectColorLoc = glGetUniformLocation(m_shaderProgram->programID, "objectColor");
	GLint lightAmbient = glGetUniformLocation(m_shaderProgram->programID, "light.ambient");
	GLint lightDiffuse = glGetUniformLocation(m_shaderProgram->programID, "light.diffuse");
	GLint lightSpecular = glGetUniformLocation(m_shaderProgram->programID, "light.specular");
	GLint lightDirection = glGetUniformLocation(m_shaderProgram->programID, "light.direction");
	GLint viewPosLoc = glGetUniformLocation(m_shaderProgram->programID, "viewPos");

	glUniform3f(objectColorLoc, 0.55f, 0.8f, 0.54f);
	glUniform3f(lightAmbient, lightCaster->getAmbient().x, lightCaster->getAmbient().y, lightCaster->getAmbient().z);
	glUniform3f(lightDiffuse, lightCaster->getDiffuse().x, lightCaster->getDiffuse().y, lightCaster->getDiffuse().z);
	glUniform3f(lightSpecular, lightCaster->getSpecular().x, lightCaster->getSpecular().y, lightCaster->getSpecular().z);
	glUniform3f(lightDirection, lightCaster->getDirection().x, lightCaster->getDirection().y, lightCaster->getDirection().z);
	glUniform3f(viewPosLoc, viewPosition.x, viewPosition.y, viewPosition.z);

	GLuint modelLoc = glGetUniformLocation(m_shaderProgram->programID, "model");
	GLuint viewLoc = glGetUniformLocation(m_shaderProgram->programID, "view");
	GLuint projLoc = glGetUniformLocation(m_shaderProgram->programID, "projection");

	glm::mat4 model;
	model = glm::translate(model, m_position);
	model = glm::scale(model, glm::vec3(1.0f, 0.06f, 1.0f));

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

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
