#pragma once

#include "LightCaster.h"

class DirectionalLight : public LightCaster
{

public:

	DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction);
	~DirectionalLight();

	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
	glm::vec3 getDirection();

private:

	glm::vec3 m_ambient, m_diffuse, m_specular;
	glm::vec3 m_direction;
};

