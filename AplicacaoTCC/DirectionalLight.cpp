#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction)
{
	m_ambient = ambient;
	m_diffuse = diffuse;
	m_specular = specular;
	m_direction = direction;
}

DirectionalLight::~DirectionalLight()
{
}

glm::vec3 DirectionalLight::getAmbient()
{
	return m_ambient;
}

glm::vec3 DirectionalLight::getDiffuse()
{
	return m_diffuse;
}

glm::vec3 DirectionalLight::getSpecular()
{
	return m_specular;
}

glm::vec3 DirectionalLight::getDirection()
{
	return m_direction;
}
