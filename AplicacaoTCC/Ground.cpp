#include "Ground.h"

Ground::Ground(ShaderProgram* shaderProgram, GLfloat size, glm::vec3 position, bool enablePhysics)
{
	m_shaderProgram = shaderProgram;
	m_position = position;
	m_side = size;
	
	hasPhysics = enablePhysics;
	m_shape = new btStaticPlaneShape(btVector3(0, 1.0, 0), -m_side + 1);		// O chão sempre terá 1 de altura
	m_motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
		btVector3(btScalar(m_position.x), btScalar(m_position.y), btScalar(m_position.z))));
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(0, m_motionState, m_shape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rigidBodyCI);
}

Ground::~Ground()
{
}

// Configura os vértices na memória
void Ground::setup()
{
	GLfloat newHeight = -m_side + 1.0f;		// Faz com que a forma tenha apenas 1.0f de altura sempre

	//			C
	//      v6----- v5
	//     /|      /|
	//    v1------v0|
	// E  | |     | |    D
	//    | |v7---|-|v4
	//    |/      |/
	//    v2------v3
	//		   B

	GLfloat vertices[] = {
		// Trás
		-m_side,	-m_side, -m_side,   0.0f,  0.0f, -1.0f,		// v7
		 m_side,	-m_side, -m_side,   0.0f,  0.0f, -1.0f,		// v4
		 m_side,  newHeight, -m_side,   0.0f,  0.0f, -1.0f,		// v5
		 m_side,  newHeight, -m_side,   0.0f,  0.0f, -1.0f,		// v5
		-m_side,  newHeight, -m_side,   0.0f,  0.0f, -1.0f,		// v6
		-m_side,	-m_side, -m_side,   0.0f,  0.0f, -1.0f,		// v7

		// Frente
		-m_side,	-m_side,  m_side,   0.0f,  0.0f,  1.0f,		// v2
		 m_side,	-m_side,  m_side,   0.0f,  0.0f,  1.0f,		// v3
		 m_side,  newHeight,  m_side,   0.0f,  0.0f,  1.0f,		// v0
		 m_side,  newHeight,  m_side,   0.0f,  0.0f,  1.0f,		// v0
		-m_side,  newHeight,  m_side,   0.0f,  0.0f,  1.0f,		// v1
		-m_side,	-m_side,  m_side,   0.0f,  0.0f,  1.0f,		// v2

		// Esquerda
		-m_side,  newHeight,  m_side,  -1.0f,  0.0f,  0.0f,		// v1
		-m_side,  newHeight, -m_side,  -1.0f,  0.0f,  0.0f,		// v6
		-m_side,	-m_side, -m_side,  -1.0f,  0.0f,  0.0f,		// v7
		-m_side,	-m_side, -m_side,  -1.0f,  0.0f,  0.0f,		// v7
		-m_side,	-m_side,  m_side,  -1.0f,  0.0f,  0.0f,		// v2
		-m_side,  newHeight,  m_side,  -1.0f,  0.0f,  0.0f,		// v1

		// Direita
		 m_side,  newHeight,  m_side,   1.0f,  0.0f,  0.0f,		// v0
		 m_side,  newHeight, -m_side,   1.0f,  0.0f,  0.0f,		// v5
		 m_side,	-m_side, -m_side,   1.0f,  0.0f,  0.0f,		// v4
		 m_side,	-m_side, -m_side,   1.0f,  0.0f,  0.0f,		// v4
		 m_side,	-m_side,  m_side,   1.0f,  0.0f,  0.0f,		// v3
		 m_side,  newHeight,  m_side,   1.0f,  0.0f,  0.0f,		// v0

		// Baixo
		-m_side,	-m_side, -m_side,   0.0f, -1.0f,  0.0f,		// v7
		 m_side,	-m_side, -m_side,   0.0f, -1.0f,  0.0f,		// v4
		 m_side,	-m_side,  m_side,   0.0f, -1.0f,  0.0f,		// v3
		 m_side,	-m_side,  m_side,   0.0f, -1.0f,  0.0f,		// v3
		-m_side,	-m_side,  m_side,   0.0f, -1.0f,  0.0f,		// v2
		-m_side,	-m_side, -m_side,   0.0f, -1.0f,  0.0f,		// v7

		// Cima
		-m_side,  newHeight, -m_side,   0.0f,  1.0f,  0.0f,		// v6
		 m_side,  newHeight, -m_side,   0.0f,  1.0f,  0.0f,		// v5
		 m_side,  newHeight,  m_side,   0.0f,  1.0f,  0.0f,		// v0
		 m_side,  newHeight,  m_side,   0.0f,  1.0f,  0.0f,		// v0
		-m_side,  newHeight,  m_side,   0.0f,  1.0f,  0.0f,		// v1
		-m_side,  newHeight, -m_side,   0.0f,  1.0f,  0.0f		// v6
	};

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO

	m_objectColorLoc = glGetUniformLocation(m_shaderProgram->programID, "objectColor");
	m_lightAmbient = glGetUniformLocation(m_shaderProgram->programID, "light.ambient");
	m_lightDiffuse = glGetUniformLocation(m_shaderProgram->programID, "light.diffuse");
	m_lightSpecular = glGetUniformLocation(m_shaderProgram->programID, "light.specular");
	m_lightDirection = glGetUniformLocation(m_shaderProgram->programID, "light.direction");
	m_viewPosLoc = glGetUniformLocation(m_shaderProgram->programID, "viewPos");

	m_modelLoc = glGetUniformLocation(m_shaderProgram->programID, "model");
	m_viewLoc = glGetUniformLocation(m_shaderProgram->programID, "view");
	m_projLoc = glGetUniformLocation(m_shaderProgram->programID, "projection");
}

void Ground::updatePhysics()
{
}

// Renderiza o objeto
void Ground::update(glm::vec3 viewPosition, glm::mat4 view, glm::mat4 projection, LightCaster* lightCaster)
{
	m_shaderProgram->use();
	
	glUniform3f(m_objectColorLoc, 0.84f, 1.0f, 1.0f);
	glUniform3f(m_lightAmbient, lightCaster->getAmbient().x, lightCaster->getAmbient().y, lightCaster->getAmbient().z);
	glUniform3f(m_lightDiffuse, lightCaster->getDiffuse().x, lightCaster->getDiffuse().y, lightCaster->getDiffuse().z);
	glUniform3f(m_lightSpecular, lightCaster->getSpecular().x, lightCaster->getSpecular().y, lightCaster->getSpecular().z);
	glUniform3f(m_lightDirection, lightCaster->getDirection().x, lightCaster->getDirection().y, lightCaster->getDirection().z);
	glUniform3f(m_viewPosLoc, viewPosition.x, viewPosition.y, viewPosition.z);

	glm::mat4 model;
	model = glm::translate(model, m_position);

	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(m_projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

// Limpa os dados
void Ground::clean()
{
	delete m_shaderProgram;
	delete m_shape;
	delete m_rigidBody->getMotionState();
	delete m_rigidBody;
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

// Retorna o rigidbody
btRigidBody* Ground::getRigidBody()
{
	return m_rigidBody;
}
