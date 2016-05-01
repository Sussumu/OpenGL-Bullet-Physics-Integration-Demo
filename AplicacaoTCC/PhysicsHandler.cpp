#include "PhysicsHandler.h"

PhysicsHandler::PhysicsHandler()
{
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -9.8, 0));
}

PhysicsHandler::~PhysicsHandler()
{
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
}

// Adiciona os rigidbodies de cada objeto no mundo
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

// Realiza a etapa de c�lculo de f�sica baseado no tempo passado desde o �ltimo frame
void PhysicsHandler::stepSimulation(float deltaTime)
{
	dynamicsWorld->stepSimulation(deltaTime/1000.0f);
}

// Limpa os dados 
void PhysicsHandler::cleanRigidBodies(std::vector<GameObject*> gameObjectsList)
{
	for each (GameObject* gameObject in gameObjectsList)
	{
		if (gameObject->hasPhysics)
		{
			dynamicsWorld->removeRigidBody(gameObject->getRigidBody());
		}
	}
}
