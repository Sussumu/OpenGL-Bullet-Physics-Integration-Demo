#include "GravityScenario.h"

GravityScenario::GravityScenario()
{
	cube = nullptr;
	diffuseSource = nullptr;
	ground = nullptr;
	directionalLight = nullptr;

	m_shaderProgram = new ShaderProgram();
	m_physicsHandler = new PhysicsHandler();

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
}

// Configura os gameobjects, iluminação e física
void GravityScenario::setupScenario()
{
	// Cubo
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
		cube = new Cube(m_shaderProgram, rand()%10/5+1, glm::vec3(rand()%10, rand()%100+10, rand()%10), 1.0f, true);
		m_objectsList.push_back(cube);
	}

	// Ground
	ground = new Ground(m_shaderProgram, 40.0f, glm::vec3(0, 0, 0), true);
	m_objectsList.push_back(ground);

	// Directional light
	glm::vec3 ambient(0.8f, 0.8f, 0.8f);
	glm::vec3 diffuse(0.5f, 0.5f, 0.5f);
	glm::vec3 specular(1.0f);
	glm::vec3 direction(-30.0f, -40.0f, -20.0f);
	directionalLight = new DirectionalLight(ambient, diffuse, specular, direction);
	
	for each (GameObject* gameObject in m_objectsList)
	{
		gameObject->setup();
	}

	m_physicsHandler->setupRigidBodies(m_objectsList);
}

// Atualiza as matrizes da câmera para renderizar os objetos de forma correta
void GravityScenario::updateCamera(Camera* camera)
{
	view = camera->GetViewMatrix(); // LookAt
	projection = glm::perspective(camera->Zoom, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
}

// Executa os cálculos de física e atualiza cada objeto
void GravityScenario::updatePhysics(float deltaTime)
{
	m_physicsHandler->stepSimulation(deltaTime);

	for each (GameObject* gameObject in m_objectsList)
	{
		gameObject->updatePhysics();
	}
}

// Renderiza o cenário
void GravityScenario::renderScenario(Camera* camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.34, 0.78, 0.76, 1.0);

	for each (GameObject* gameObject in m_objectsList)
	{
		// Cada objeto precisa da posição da câmera e das matrizes view e projection para serem desenhados
		gameObject->update(camera->Position, view, projection, directionalLight);
	}

	updateCamera(camera);
}

// Limpa os gameobjects
void GravityScenario::cleanScenario()
{
	for each (GameObject* gameObject in m_objectsList)
	{
		gameObject->clean();
	}

	delete cube, diffuseSource, ground;
	delete directionalLight;
	delete m_shaderProgram;
	delete m_physicsHandler;
}