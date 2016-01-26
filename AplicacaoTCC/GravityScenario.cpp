#include "GravityScenario.h"

GravityScenario::GravityScenario()
{
	// Câmera
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	initShaders();
	setupScenario();

	m_physicsHandler = new PhysicsHandler();
}

GravityScenario::~GravityScenario()
{
}

void GravityScenario::initShaders()
{
	m_shaderProgram->compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	//m_shaderProgram->addAttribute("vertexPosition");
	//m_shaderProgram->addAttribute("vertexColor");
	m_shaderProgram->linkShaders();
	
	m_lightShaderProgram->compileShaders("Shaders/lightShading.vert", "Shaders/lightShading.frag");
	//m_lightShaderProgram->addAttribute("vertexPosition");
	//m_lightShaderProgram->addAttribute("vertexColor");
	m_lightShaderProgram->linkShaders();

	m_shaderPrograms.push_back(m_shaderProgram);		// 0
	m_shaderPrograms.push_back(m_lightShaderProgram);	// 1
}

void GravityScenario::setupScenario()
{
	// Cubo
	GLfloat vertices[] ={
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  -1.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  -1.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  -1.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  -1.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  -1.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  -1.0f,
							   		 	    
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   1.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   1.0f,
		 0.5f,  0.5f,  0.5f,   0.0f, 0.0f,   1.0f,
		 0.5f,  0.5f,  0.5f,   0.0f, 0.0f,   1.0f,
		-0.5f,  0.5f,  0.5f,   0.0f, 0.0f,   1.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   1.0f,
							   		 	    
		-0.5f,  0.5f,  0.5f, - 1.0f, 0.0f,   0.0f,
		-0.5f,  0.5f, -0.5f, - 1.0f, 0.0f,   0.0f,
		-0.5f, -0.5f, -0.5f, - 1.0f, 0.0f,   0.0f,
		-0.5f, -0.5f, -0.5f, - 1.0f, 0.0f,   0.0f,
		-0.5f, -0.5f,  0.5f, - 1.0f, 0.0f,   0.0f,
		-0.5f,  0.5f,  0.5f, - 1.0f, 0.0f,   0.0f,
							   		 	    
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 0.0f,   0.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   0.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   0.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   0.0f,
							   		 	    
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   0.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   0.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, 1.0f,   0.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, 1.0f,   0.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, 1.0f,   0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   0.0f,
							   		 	    
		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f,
		 0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   0.0f,
		 0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   0.0f,
		-0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   0.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f
	};
	//glm::vec3 position[] = {
	//	glm::vec3( 0.0f,  0.0f,   0.0f),
	//	glm::vec3( 2.0f,  5.0f, -15.0f),
	//	glm::vec3(-1.5f, -2.2f,  -2.5f),
	//	glm::vec3(-3.8f, -2.0f, -12.3f),
	//	glm::vec3( 2.4f, -0.4f,  -3.5f),
	//	glm::vec3(-1.7f,  3.0f,  -7.5f),
	//	glm::vec3( 1.3f, -2.0f,  -2.5f),
	//	glm::vec3( 1.5f,  2.0f,  -2.5f),
	//	glm::vec3( 1.5f,  0.2f,  -1.5f),
	//	glm::vec3(-1.3f,  1.0f,  -1.5f)
	//};
	cube = new Cube(m_shaderPrograms.at(0), vertices, glm::vec3(0, 0, 0));
	m_objectsList.push_back(cube);
	
	// Iluminação
	diffuseSource = new DiffuseIluminationSource(m_shaderPrograms, vertices, glm::vec3(0, 0, 0));
	m_objectsList.push_back(diffuseSource);

	Scenario::objectsList = m_objectsList;
	Scenario::setupScenario();

	m_physicsHandler->setupRigidBodies(m_objectsList);
}

void GravityScenario::updateCamera()
{
	glm::mat4 view;
	view = camera->GetViewMatrix();
	glm::mat4 projection;
	projection = glm::perspective(camera->Zoom, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);

	//GLint modelLoc = glGetUniformLocation(m_shaderProgram->programID, "model");
	GLint viewLoc = glGetUniformLocation(m_shaderProgram->programID, "view");
	GLint projLoc = glGetUniformLocation(m_shaderProgram->programID, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void GravityScenario::renderScenario()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Scenario::renderScenario();
}

void GravityScenario::cleanScenario()
{
	Scenario::objectsList = m_objectsList;
	Scenario::cleanScenario();
}