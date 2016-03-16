#include "GravityScenario.h"

GravityScenario::GravityScenario()
{
	initShaders();
	setupScenario();
}

GravityScenario::~GravityScenario()
{
}

void GravityScenario::initShaders()
{
	m_shaderProgram->compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_shaderProgram->linkShaders();
	
	m_lightShaderProgram->compileShaders("Shaders/lightShading.vert", "Shaders/lightShading.frag");
	m_lightShaderProgram->linkShaders();
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
	cube = new Cube(m_shaderProgram, vertices2, glm::vec3(0, 30, 0), 1.0f, true);
	m_objectsList.push_back(cube);

	cube = new Cube(m_shaderProgram, vertices2, glm::vec3(0, -10, 0), 0.0f, false);
	m_objectsList.push_back(cube);
	
	// Iluminação
	//diffuseSource = new DiffuseIluminationSource(m_shaderPrograms, vertices2, glm::vec3(2, 9, 2), false);
	//m_objectsList.push_back(diffuseSource);

	for each (GameObject* gameObject in m_objectsList)
	{
		gameObject->setup();
	}

	m_physicsHandler->setupRigidBodies(m_objectsList);
}

void GravityScenario::updateCamera(Camera* camera)
{
	view = camera->GetViewMatrix(); // LookAt
	projection = glm::perspective(camera->Zoom, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
}

void GravityScenario::updatePhysics(int deltaTime)
{
	m_physicsHandler->stepSimulation(deltaTime);

	for each (GameObject* gameObject in m_objectsList)
	{
		gameObject->updatePhysics();
	}
}

void GravityScenario::renderScenario(Camera* camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.34, 0.78, 0.756, 1.0);

	for each (GameObject* gameObject in m_objectsList)
	{
		// Cada objeto precisa da posição da câmera e das matrizes view e projection para serem desenhados
		gameObject->update(camera->Position, view, projection);
	}

	updateCamera(camera);
}

void GravityScenario::cleanScenario()
{
	for each (GameObject* gameObject in m_objectsList)
	{
		gameObject->clean();
	}
}