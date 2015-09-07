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
m_broadphase(new btDbvtBroadphase()),
m_collisionConfiguration(new btDefaultCollisionConfiguration()),
m_solver(new btSequentialImpulseConstraintSolver), test(0),
IsDestroyed(false),
DestroyedIndex(0),
TickCount(0)
{
	void myTickCallback(btDynamicsWorld *world, btScalar timeStep);
	m_dispatcher = std::unique_ptr<btCollisionDispatcher>(new btCollisionDispatcher(m_collisionConfiguration.get()));

	m_dynamicsWorld = std::unique_ptr<btDiscreteDynamicsWorld>(new btDiscreteDynamicsWorld(m_dispatcher.get(), m_broadphase.get(), m_solver.get(), m_collisionConfiguration.get()));
		
	m_dynamicsWorld->setGravity(btVector3(0, -10, 0));

	m_dynamicsWorld->setInternalTickCallback(myTickCallback, static_cast<void *>(this), true);
}

Physics::~Physics(void)
{
	for_each(begin(m_rigidBodies), end(m_rigidBodies), [&](const unique_ptr<btRigidBody>& rigidBody)
	{
		m_dynamicsWorld->removeRigidBody(rigidBody.get());
		delete rigidBody->getMotionState();
	});

	m_rigidBodies.clear();
}

void Physics::Update()
{
	m_dynamicsWorld->stepSimulation(1 / 60.f, 10);
//Разрушаемость - не решена
	//auto AmmoObjectForContactTest = m_dynamicsWorld->getCollisionObjectArray().at(m_dynamicsWorld->getCollisionObjectArray().size() - 1);
	//int objectQuantity = m_dynamicsWorld->getCollisionObjectArray().size();
	
	
//	for (int i = 2; i < objectQuantity - 2; i++) // первые объекты - земля и платформы, последний - "оружие"
//	{
//		/*auto ObjectForContactTest = m_dynamicsWorld->getCollisionObjectArray().at(m_dynamicsWorld->getCollisionObjectArray().size() - i);
//
//		m_dynamicsWorld->contactPairTest(ObjectForContactTest, AmmoObjectForContactTest, result);
//		
//		if (result.m_connected == true){*/
//
//			btVector3 objectVelocityVector = this->m_rigidBodies.at(m_rigidBodies.size() - i)->getVelocityInLocalPoint(btVector3(0.2f, 0.2f, 0.2f));
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
//		//auto force = this->m_rigidBodies.at(3)->();
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

	m_dynamicsWorld->addRigidBody(groundRigidBody);
	m_shapes.push_back(std::unique_ptr<btCollisionShape>(collisionShape));
	m_rigidBodies.push_back(std::unique_ptr<btRigidBody>(groundRigidBody));
	states.push_back(std::unique_ptr<btMotionState>(motionState));
}
