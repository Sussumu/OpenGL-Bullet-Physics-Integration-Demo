#pragma once

#include "Camera.h"
#include <string>
#include <glm\glm.hpp>
#include <Bullet/btBulletDynamicsCommon.h>

class GameObject
{
public:

	GameObject();
	~GameObject();

	bool hasPhysics;
	std::string name;

	virtual btRigidBody* getRigidBody() = 0;

	virtual void setup() = 0;
	virtual void updatePhysics() = 0;
	virtual void update(glm::vec3 viewPosition, glm::mat4 view, glm::mat4 projection) = 0;
	//virtual void update(Camera* camera) = 0;
	virtual void clean() = 0;
};

