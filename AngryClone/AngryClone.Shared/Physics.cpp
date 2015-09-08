#include "pch.h"
#include "Physics.h"
#include <algorithm>

using namespace std;

//RESULT CALLBACK FOR DETECTION OF COLLIDING PAIRS; found code here ---> http://www.ogre3d.org/forums/viewtopic.php?f=2&t=64815&p=428681
class MyContactResultCallback : public btCollisionWorld::ContactResultCallback
{
public:
	bool m_connected;
	MyContactResultCallback() :m_connected(false)
	{
	}
	btScalar   btCollisionWorld::ContactResultCallback::addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0, int partId0, int index0, const btCollisionObjectWrapper* colObj1, int partId1, int index1)
	{
		if (cp.getDistance() <= 0)
		{
			m_connected = true;
			return 1.f;
		}
		else{
			m_connected = false;
			return 0.f;
		}
	}
};
MyContactResultCallback result;
//END OF CALLBACK CODE

Physics::Physics(void) :
Broadphase(new btDbvtBroadphase()),
CollisionConfiguration(new btDefaultCollisionConfiguration()),
ConstraintSolver(new btSequentialImpulseConstraintSolver),
IsDestroyed(false),
DestroyedIndex(0),
TickCount(0)
{
	void myTickCallback(btDynamicsWorld *world, btScalar timeStep);

	CollisionDispatcher = std::unique_ptr<btCollisionDispatcher>(new btCollisionDispatcher(CollisionConfiguration.get()));
	DynamicsWorld = std::unique_ptr<btDiscreteDynamicsWorld>(new btDiscreteDynamicsWorld(CollisionDispatcher.get(), Broadphase.get(), ConstraintSolver.get(), CollisionConfiguration.get()));
		
	DynamicsWorld->setGravity(btVector3(0, -10, 0));
	DynamicsWorld->setInternalTickCallback(myTickCallback, static_cast<void *>(this), true);
}

Physics::~Physics(void)
{
	for_each(begin(RigidBodies), end(RigidBodies), [&](const unique_ptr<btRigidBody>& rigidBody)
	{
		DynamicsWorld->removeRigidBody(rigidBody.get());
		delete rigidBody->getMotionState();
	});

	RigidBodies.clear();
}

void Physics::Update()
{
	DynamicsWorld->stepSimulation(1 / 60.f, 10);
//Разрушаемость - не решена
	//auto AmmoObjectForContactTest = DynamicsWorld->getCollisionObjectArray().at(DynamicsWorld->getCollisionObjectArray().size() - 1);
	//int objectQuantity = DynamicsWorld->getCollisionObjectArray().size();
	
	
//	for (int i = 2; i < objectQuantity - 2; i++) // первые объекты - земля и платформы, последний - "оружие"
//	{
//		/*auto ObjectForContactTest = DynamicsWorld->getCollisionObjectArray().at(DynamicsWorld->getCollisionObjectArray().size() - i);
//
//		DynamicsWorld->contactPairTest(ObjectForContactTest, AmmoObjectForContactTest, result);
//		
//		if (result.m_connected == true){*/
//
//			btVector3 objectVelocityVector = this->RigidBodies.at(RigidBodies.size() - i)->getVelocityInLocalPoint(btVector3(0.2f, 0.2f, 0.2f));
//			btScalar objectVelocity = sqrt(objectVelocityVector.getX() * objectVelocityVector.getX() +
//										objectVelocityVector.getY() * objectVelocityVector.getY() +
//										objectVelocityVector.getZ() * objectVelocityVector.getZ());
//
//			if (objectVelocity > 4.0f && TickCount == 0 && IsDestroyed == false)
//		{
//			IsDestroyed = true;
//			TickCount = 5;
//			DestroyedIndex = objectQuantity - i;
//			break;
//		}
//		//auto force = this->RigidBodies.at(3)->();
//	//}
//}

 //	if (IsDestroyed && TickCount > 0)
	//{
	//	TickCount--;
	//}

}

void myTickCallback(btDynamicsWorld *world, btScalar timeStep) {
	int numManifolds = world->getDispatcher()->getNumManifolds();
	for (int i = 0; i<numManifolds; i++)
	{
		btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = (btCollisionObject*)(contactManifold->getBody0());
		btCollisionObject* obB = (btCollisionObject*)(contactManifold->getBody1());

		int numContacts = contactManifold->getNumContacts();
		for (int j = 0; j<numContacts; j++)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance()<0.f)
			{
				const btVector3& ptA = pt.getPositionWorldOnA();
				const btVector3& ptB = pt.getPositionWorldOnB();
				const btVector3& normalOnB = pt.m_normalWorldOnB;
			}
		}
	}
}

void Physics::AddPhysicalObject(btCollisionShape* collisionShape, btMotionState* motionState, btScalar mass, const btVector3& inertia)
{
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(mass, motionState, collisionShape, inertia);
	
	auto groundRigidBody = new btRigidBody(groundRigidBodyCI);

	DynamicsWorld->addRigidBody(groundRigidBody);
	ObjectsCollisionShapes.push_back(std::unique_ptr<btCollisionShape>(collisionShape));
	RigidBodies.push_back(std::unique_ptr<btRigidBody>(groundRigidBody));
	ObjectsMotionStates.push_back(std::unique_ptr<btMotionState>(motionState));
}
