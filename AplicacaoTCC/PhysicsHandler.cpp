#include "PhysicsHandler.h"

PhysicsHandler::PhysicsHandler()
{
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

PhysicsHandler::~PhysicsHandler()
{
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
}

void PhysicsHandler::setupRigidBodies(std::vector<GameObject*> gameObjectsList)
{
	for each (GameObject* gameObject in gameObjectsList)
	{
		if (gameObject->hasPhysics)
		{
			dynamicsWorld->addRigidBody(gameObject->getRigidBody());
		}
	}
}
