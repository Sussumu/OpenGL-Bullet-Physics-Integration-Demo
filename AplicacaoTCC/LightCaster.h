#pragma once

#include <glm/glm.hpp>

class LightCaster
{

public:
	LightCaster();
	~LightCaster();

	virtual glm::vec3 getAmbient();
	virtual glm::vec3 getDiffuse();
	virtual glm::vec3 getSpecular();
	virtual glm::vec3 getDirection();
};

