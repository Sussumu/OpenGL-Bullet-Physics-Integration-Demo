#pragma once

#include "GameObject.h"
#include <Bullet/btBulletDynamicsCommon.h>
#include <vector>

class PhysicsHandler
{
public:
	PhysicsHandler();
	~PhysicsHandler();

	void setupRigidBodies(std::vector<GameObject*> gameObjectsList);
	void stepSimulation(float deltaTime);
	void cleanRigidBodies(std::vector<GameObject*> gameObjectsList);

private:
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
};

