#pragma once

#include <Bullet/btBulletDynamicsCommon.h>

class GameObject
{
public:

	GameObject();
	~GameObject();

	bool hasPhysics;

	virtual btRigidBody* getRigidBody() = 0;

	virtual void setup() = 0;
	virtual void updatePhysics() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
};

