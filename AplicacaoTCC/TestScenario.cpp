#include "TestScenario.h"

TestScenario::TestScenario()
{
	initShaders();
	setupScenario();
}

TestScenario::~TestScenario()
{
}

void TestScenario::initShaders()
{
	m_shaderProgram->compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_shaderProgram->linkShaders();

	m_lightShaderProgram->compileShaders("Shaders/lightShading.vert", "Shaders/lightShading.frag");
	m_lightShaderProgram->linkShaders();

	m_shaderPrograms.push_back(m_shaderProgram);		// 0
	m_shaderPrograms.push_back(m_lightShaderProgram);	// 1
}

void TestScenario::updateCamera(Camera* camera)
{
	view = camera->GetViewMatrix(); // LookAt
	projection = glm::perspective(camera->Zoom, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
}

void TestScenario::setupScenario()
{
	///////////////////////////////////////////////////////////////////////////
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	// First, set the container's VAO (and VBO)
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	///

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the normal vectors
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	///////////////////////////////////////////////////////////////////////////
}

void TestScenario::renderScenario(Camera* camera)
{
	// (87, 199, 193, 1.0)
	glClearColor(0.34, 0.78, 0.756, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	///////////////////////////////////////////////////////////////////////////
	// Seleciona o shader 
	m_shaderPrograms[0]->use();
	GLint objectColorLoc = glGetUniformLocation(m_shaderPrograms[0]->programID, "objectColor");
	GLint lightColorLoc = glGetUniformLocation(m_shaderPrograms[0]->programID, "lightColor");
	GLint lightPosLoc = glGetUniformLocation(m_shaderPrograms[0]->programID, "lightPos");
	GLint viewPosLoc = glGetUniformLocation(m_shaderPrograms[0]->programID, "viewPos");
	// Seta as variáveis
	glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);							
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);								
	glUniform3f(lightPosLoc, 1.2f, 1.0f, 2.0f);
	glUniform3f(viewPosLoc, camera->Position.x, camera->Position.y, camera->Position.z);
	// Configura as matrizes
	modelLoc = glGetUniformLocation(m_shaderPrograms[0]->programID, "model");
	viewLoc = glGetUniformLocation(m_shaderPrograms[0]->programID, "view");
	projLoc = glGetUniformLocation(m_shaderPrograms[0]->programID, "projection");

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	// Seleciona o shader 
	m_shaderPrograms[1]->use();
	modelLoc = glGetUniformLocation(m_shaderPrograms[1]->programID, "model");
	viewLoc = glGetUniformLocation(m_shaderPrograms[1]->programID, "view");
	projLoc = glGetUniformLocation(m_shaderPrograms[1]->programID, "projection");
	// Configura as matrizes
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.5f));

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	///////////////////////////////////////////////////////////////////////////

	updateCamera(camera);
}

void TestScenario::cleanScenario()
{
	//m_physicsHandler->cleanRigidBodies(m_objectsList);
	Scenario::cleanScenario();

	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}
