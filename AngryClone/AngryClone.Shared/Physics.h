#pragma once
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
class Physics
{
public:
	Physics(void);
	~Physics(void);

	void Update();
	void AddPhysicalObject(btCollisionShape* collisionShape, btMotionState* motionState, btScalar mass, const btVector3& inertia);
private:
	Physics(const Physics&){}
	Physics& operator=(const Physics&) { return *this; }

	std::unique_ptr<btBroadphaseInterface> Broadphase;
	std::unique_ptr<btDefaultCollisionConfiguration> CollisionConfiguration;
	std::unique_ptr<btCollisionDispatcher> CollisionDispatcher;
	std::unique_ptr<btSequentialImpulseConstraintSolver> ConstraintSolver;
	
public:
	std::unique_ptr<btDiscreteDynamicsWorld> DynamicsWorld;
	std::vector<std::unique_ptr<btCollisionShape>> ObjectsCollisionShapes;
	std::vector<std::unique_ptr<btRigidBody>> RigidBodies;
	std::vector<std::unique_ptr<btMotionState>> ObjectsMotionStates;
	
	bool IsDestroyed;
	short TickCount;
	short DestroyedIndex;
};

