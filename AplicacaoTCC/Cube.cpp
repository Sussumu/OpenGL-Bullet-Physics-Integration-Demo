#include "Cube.h"

Cube::Cube(ShaderProgram* shaderProgram, GLfloat* vertices, glm::vec3 position, float mass, bool enablePhysics)
{
	m_shaderProgram = shaderProgram;
	m_vertices = (GLfloat*)malloc(sizeof vertices);
	memcpy(m_vertices, vertices, sizeof(vertices));
	m_position = position;

	m_mass = mass;
	hasPhysics = enablePhysics;
	shape = new btBoxShape(btVector3(1, 1, 1));
	motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
				   btVector3(btScalar(position.x), btScalar(position.y), btScalar(position.z))));
	shape->calculateLocalInertia(mass, m_inertia);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(1, motionState, shape, m_inertia);
	rigidBody = new btRigidBody(rigidBodyCI);
}

Cube::~Cube()
{
}

void Cube::setup()
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

	// TexCoord attribute
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
#pragma endregion

#pragma region Texture
	// Load and create a texture 
	// ====================
	// Texture 1
	// ====================
	//glGenTextures(1, &m_texture1);
	//glBindTexture(GL_TEXTURE_2D, m_texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	//										  // Set our texture parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//// Set texture filtering
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//// Load, create texture and generate mipmaps
	//int width, height;
	//unsigned char* image = SOIL_load_image("Textures/container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//glGenerateMipmap(GL_TEXTURE_2D);
	//SOIL_free_image_data(image);
	//glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	// ===================
	// Texture 2
	// ===================
	//glGenTextures(1, &texture2);
	//glBindTexture(GL_TEXTURE_2D, texture2);
	//// Set our texture parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//// Set texture filtering
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//// Load, create texture and generate mipmaps
	//image = SOIL_load_image("Textures/awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//glGenerateMipmap(GL_TEXTURE_2D);
	//SOIL_free_image_data(image);
	//glBindTexture(GL_TEXTURE_2D, 0);
#pragma endregion
}

void Cube::updatePhysics()
{
	btTransform transform;
	rigidBody->getMotionState()->getWorldTransform(transform);

	m_position.x = transform.getOrigin().getX();
	m_position.y = transform.getOrigin().getY();
	m_position.z = transform.getOrigin().getZ();

	transform.getBasis().getEulerYPR(yaw, pitch, roll);
}

void Cube::update()
{
	m_shaderProgram->use();

#pragma region Texture
	// Bind Textures using texture units
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, m_texture1);
	//glUniform1i(glGetUniformLocation(shaderProgram.programID, "ourTexture1"), 0);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, m_texture2);
	//glUniform1i(glGetUniformLocation(shaderProgram.Program, "ourTexture2"), 1);
#pragma endregion

#pragma region Rendering
	GLint modelLoc = glGetUniformLocation(m_shaderProgram->programID, "model");
	GLint viewLoc = glGetUniformLocation(m_shaderProgram->programID, "view");
	GLint projLoc = glGetUniformLocation(m_shaderProgram->programID, "projection");

	GLint objectColorLoc = glGetUniformLocation(m_shaderProgram->programID, "objectColor");
	GLint lightColorLoc = glGetUniformLocation(m_shaderProgram->programID, "lightColor");
	GLint lightPosLoc = glGetUniformLocation(m_shaderProgram->programID, "lightPos");
	GLint viewPosLoc = glGetUniformLocation(m_shaderProgram->programID, "viewPos");

	glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(lightColorLoc, 1.0f, 0.5f, 1.0f);
	//glUniform3f(viewPosLoc, Simulador::getCamera()->Position.x, Simulador::getCamera()->Position.y, Simulador::getCamera()->Position.z);  //camera.Position.x, camera.Position.y, camera.Position.z);

	glBindVertexArray(m_VAO);
	glm::mat4 model;
	model = glm::translate(model, m_position);
	model = glm::rotate(model, yaw, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, pitch, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, roll, glm::vec3(1.0f, 0.0f, 1.0f));

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);

	m_shaderProgram->unuse();
#pragma endregion
}

void Cube::clean()
{
	delete shape;
	delete rigidBody->getMotionState();
	delete rigidBody;
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

btRigidBody* Cube::getRigidBody()
{
	return rigidBody;
}
