#include "GravityScenario.h"

GravityScenario::GravityScenario()
{
	// Câmera
	//camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

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
	// Ground
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
	ground = new Ground(m_shaderProgram, vertices, glm::vec3(0, 0, 0), false);
	m_objectsList.push_back(ground);

	// Cubo
	GLfloat vertices2[] ={
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
	cube = new Cube(m_shaderPrograms.at(0), vertices2, glm::vec3(0, 10, 0), 1.0f, true);
	m_objectsList.push_back(cube);
	
	// Iluminação
	//diffuseSource = new DiffuseIluminationSource(m_shaderPrograms, vertices2, glm::vec3(2, 9, 2), false);
	//m_objectsList.push_back(diffuseSource);

	Scenario::objectsList = m_objectsList;
	Scenario::setupScenario();

	m_physicsHandler->setupRigidBodies(m_objectsList);
}

void GravityScenario::updateCamera(Camera* camera)
{
	view = camera->GetViewMatrix(); // LookAt
	projection = glm::perspective(camera->Zoom, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);

	GLint modelLoc = glGetUniformLocation(m_shaderProgram->programID, "model");
	GLint viewLoc = glGetUniformLocation(m_shaderProgram->programID, "view");
	GLint projLoc = glGetUniformLocation(m_shaderProgram->programID, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void GravityScenario::renderScenario(Camera* camera)
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.34, 0.78, 0.756, 1.0);

	m_shaderProgram->use();
	updateCamera(camera);
	m_shaderProgram->unuse();

	Scenario::renderScenario(camera);
}

void GravityScenario::cleanScenario()
{
	m_physicsHandler->cleanRigidBodies(m_objectsList);
	Scenario::cleanScenario();
}