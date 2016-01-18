#include <GL/glew.h>
#include <glm/glm.hpp>

#include "GravityScenario.h"

GravityScenario::GravityScenario()
{
	setupScenario();
}

GravityScenario::~GravityScenario()
{
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
	glm::vec3 position[] = {
		glm::vec3( 0.0f,  0.0f,   0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f,  -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f,  -3.5f),
		glm::vec3(-1.7f,  3.0f,  -7.5f),
		glm::vec3( 1.3f, -2.0f,  -2.5f),
		glm::vec3( 1.5f,  2.0f,  -2.5f),
		glm::vec3( 1.5f,  0.2f,  -1.5f),
		glm::vec3(-1.3f,  1.0f,  -1.5f)
	};
	cube = new Cube(vertices, position);
	objectsList.push_back(cube);
	
	// Iluminação
	glm::vec3 lightPosition = { 1.2f, 1.0f, 2.0f };
	diffuseSource = new DiffuseIluminationSource(&lightPosition);
	objectsList.push_back(diffuseSource);

	for each (GameObject* gameObject in objectsList)
	{
		gameObject->setup();
	}
}