#include "Cube.h"

Cube::Cube(ShaderProgram* shaderProgram, GLfloat size, glm::vec3 position, float mass, bool enablePhysics)
{
	m_shaderProgram = shaderProgram;
	m_position = position;
	m_side = size/2;

	m_mass = mass;
	hasPhysics = enablePhysics;
	m_shape = new btBoxShape(btVector3(m_side, m_side, m_side));
	m_motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
					btVector3(btScalar(m_position.x), btScalar(m_position.y), btScalar(m_position.z))));
	m_shape->calculateLocalInertia(btScalar(m_mass), m_inertia);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(m_mass, m_motionState, m_shape, m_inertia);
	rigidBodyCI.m_friction = 0.8f;
	rigidBodyCI.m_restitution = 0.1f;
	m_rigidBody = new btRigidBody(rigidBodyCI);
}

Cube::~Cube()
{
}

void Cube::setup()
{
	GLfloat vertices[] = {
		// Trás
		-m_side, -m_side, -m_side,   0.0f,  0.0f, -1.0f,		// v7
		 m_side, -m_side, -m_side,   0.0f,  0.0f, -1.0f,		// v4
		 m_side,  m_side, -m_side,   0.0f,  0.0f, -1.0f,		// v5
		 m_side,  m_side, -m_side,   0.0f,  0.0f, -1.0f,		// v5
		-m_side,  m_side, -m_side,   0.0f,  0.0f, -1.0f,		// v6
		-m_side, -m_side, -m_side,   0.0f,  0.0f, -1.0f,		// v7
											
		// Frente
		-m_side, -m_side,  m_side,   0.0f,  0.0f,  1.0f,		// v2
		 m_side, -m_side,  m_side,   0.0f,  0.0f,  1.0f,		// v3
		 m_side,  m_side,  m_side,   0.0f,  0.0f,  1.0f,		// v0
		 m_side,  m_side,  m_side,   0.0f,  0.0f,  1.0f,		// v0
		-m_side,  m_side,  m_side,   0.0f,  0.0f,  1.0f,		// v1
		-m_side, -m_side,  m_side,   0.0f,  0.0f,  1.0f,		// v2
			
		// Esquerda
		-m_side,  m_side,  m_side,  -1.0f,  0.0f,  0.0f,		// v1
		-m_side,  m_side, -m_side,  -1.0f,  0.0f,  0.0f,		// v6
		-m_side, -m_side, -m_side,  -1.0f,  0.0f,  0.0f,		// v7
		-m_side, -m_side, -m_side,  -1.0f,  0.0f,  0.0f,		// v7
		-m_side, -m_side,  m_side,  -1.0f,  0.0f,  0.0f,		// v2
		-m_side,  m_side,  m_side,  -1.0f,  0.0f,  0.0f,		// v1
				
		// Direita
		 m_side,  m_side,  m_side,   1.0f,  0.0f,  0.0f,		// v0
		 m_side,  m_side, -m_side,   1.0f,  0.0f,  0.0f,		// v5
		 m_side, -m_side, -m_side,   1.0f,  0.0f,  0.0f,		// v4
		 m_side, -m_side, -m_side,   1.0f,  0.0f,  0.0f,		// v4
		 m_side, -m_side,  m_side,   1.0f,  0.0f,  0.0f,		// v3
		 m_side,  m_side,  m_side,   1.0f,  0.0f,  0.0f,		// v0
			
		// Baixo
		-m_side, -m_side, -m_side,   0.0f, -1.0f,  0.0f,		// v7
		 m_side, -m_side, -m_side,   0.0f, -1.0f,  0.0f,		// v4
		 m_side, -m_side,  m_side,   0.0f, -1.0f,  0.0f,		// v3
		 m_side, -m_side,  m_side,   0.0f, -1.0f,  0.0f,		// v3
		-m_side, -m_side,  m_side,   0.0f, -1.0f,  0.0f,		// v2
		-m_side, -m_side, -m_side,   0.0f, -1.0f,  0.0f,		// v7
			
		// Cima
		-m_side,  m_side, -m_side,   0.0f,  1.0f,  0.0f,		// v6
		 m_side,  m_side, -m_side,   0.0f,  1.0f,  0.0f,		// v5
		 m_side,  m_side,  m_side,   0.0f,  1.0f,  0.0f,		// v0
		 m_side,  m_side,  m_side,   0.0f,  1.0f,  0.0f,		// v0
		-m_side,  m_side,  m_side,   0.0f,  1.0f,  0.0f,		// v1
		-m_side,  m_side, -m_side,   0.0f,  1.0f,  0.0f		// v6
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
	glBindVertexArray(0);
}

void Cube::updatePhysics()
{
	m_rigidBody->getMotionState()->getWorldTransform(transform);

	m_position.x = transform.getOrigin().getX();
	m_position.y = transform.getOrigin().getY();
	m_position.z = transform.getOrigin().getZ();

	transform.getBasis().getEulerYPR(m_yaw, m_pitch, m_roll);
}

void Cube::update(glm::vec3 viewPosition, glm::mat4 view, glm::mat4 projection, LightCaster* lightCaster)
{
	m_shaderProgram->use();

	GLint objectColorLoc = glGetUniformLocation(m_shaderProgram->programID, "objectColor");
	GLint lightAmbient = glGetUniformLocation(m_shaderProgram->programID, "light.ambient");
	GLint lightDiffuse = glGetUniformLocation(m_shaderProgram->programID, "light.diffuse");
	GLint lightSpecular = glGetUniformLocation(m_shaderProgram->programID, "light.specular");
	GLint lightDirection = glGetUniformLocation(m_shaderProgram->programID, "light.direction");
	GLint viewPosLoc = glGetUniformLocation(m_shaderProgram->programID, "viewPos");

	glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
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
	model = glm::rotate(model, m_yaw, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, m_pitch, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, m_roll, glm::vec3(1.0f, 0.0f, 0.0f));
	
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Cube::clean()
{
	delete m_shape;
	delete m_rigidBody->getMotionState();
	delete m_rigidBody;
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

btRigidBody* Cube::getRigidBody()
{
	return m_rigidBody;
}
