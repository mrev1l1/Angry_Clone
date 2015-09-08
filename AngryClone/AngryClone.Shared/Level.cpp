#include "pch.h"
#include "Level.h"
#include "SceneObjectMotionState.h"
#include "ModelFileHandler.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h";
#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"

Level::Level(void) : IsAmmoLost(false)
{
	btDefaultMotionState* groundMotionState(new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0))));
	auto groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

	PhysicsSimulationEngine.AddPhysicalObject(groundShape, groundMotionState, 0, btVector3(0, 0, 0));
}

void Level::InitialiseSmallRectangles(SceneObjectRenderer* smallRectanglesRenderer)
{
	auto smallRect = smallRectanglesRenderer->CreateObject();
	Objects.push_back(smallRect);

	auto x = 5.3f;
	auto y = 9.5f ;
	auto z = 0.0f;

	auto fallShape(new btBoxShape(btVector3(btScalar(0.15), btScalar(0.5), btScalar(0.5))));
	auto fallMotionState(new SceneObjectMotionState(smallRect, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	PhysicsSimulationEngine.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
	///
	auto smallRect_1 = smallRectanglesRenderer->CreateObject();
	Objects.push_back(smallRect_1);

	x = 5.3f;
	y = 11.5f;
	z = 0.0f;

	auto fallShape_1(new btBoxShape(btVector3(btScalar(0.15), btScalar(0.5), btScalar(0.5))));
	auto fallMotionState_1(new SceneObjectMotionState(smallRect_1, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btScalar mass_1 = 1;
	btVector3 fallInertia_1(0, 0, 0);
	fallShape_1->calculateLocalInertia(mass_1, fallInertia_1);
	PhysicsSimulationEngine.AddPhysicalObject(fallShape_1, fallMotionState_1, mass_1, fallInertia_1);
	//////
	auto smallRect_2 = smallRectanglesRenderer->CreateObject();
	Objects.push_back(smallRect_2);

	 x = 6.6f;
	 y = 9.5f + 2.3f;
	 z = 0.0f;

	auto fallShape_2(new btBoxShape(btVector3(btScalar(0.15), btScalar(0.5), btScalar(0.5))));
	auto fallMotionState_2(new SceneObjectMotionState(smallRect_2, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btVector3 fallInertia_2(0, 0, 0);
	fallShape_2->calculateLocalInertia(mass, fallInertia_2);
	PhysicsSimulationEngine.AddPhysicalObject(fallShape_2, fallMotionState_2, mass, fallInertia_2);
}

void Level::InitialiseNormalRectangles(SceneObjectRenderer* normallRectanglesRenderer)
{
	auto normallRect = normallRectanglesRenderer->CreateObject();
	Objects.push_back(normallRect);

	auto x = 6.3f;
	auto y = 9.5f;
	auto z = 0.0f;

	auto fallShape(new btBoxShape(btVector3(btScalar(0.15), btScalar(1.0), btScalar(0.5))));
	auto fallMotionState(new SceneObjectMotionState(normallRect, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	PhysicsSimulationEngine.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
}

void Level::InitialiseLargeRectangles(SceneObjectRenderer* largeRectanglesRenderer)
{
	auto largeRect = largeRectanglesRenderer->CreateObject();
	Objects.push_back(largeRect);

	auto x =  5.3f;
	auto y = 11.5f;
	auto z = 0.0f;

	auto fallShape(new btBoxShape(btVector3(btScalar(1.5), btScalar(0.15), btScalar(0.5))));
	auto fallMotionState(new SceneObjectMotionState(largeRect, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	PhysicsSimulationEngine.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
	/////
	auto largeRect_1 = largeRectanglesRenderer->CreateObject();
	Objects.push_back(largeRect_1);

	 x = 6.6+1.4f;
	 y = 9.5 + 3.3f ;
	 z = 0.0f;

	auto fallShape_1(new btBoxShape(btVector3(btScalar(1.5), btScalar(0.15), btScalar(0.5))));
	auto fallMotionState_1(new SceneObjectMotionState(largeRect_1, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btVector3 fallInertia_1(0, 0, 0);
	fallShape_1->calculateLocalInertia(mass, fallInertia_1);
	PhysicsSimulationEngine.AddPhysicalObject(fallShape_1, fallMotionState_1, mass, fallInertia_1);
}

void Level::InitialiseExtraLargeRectangles(SceneObjectRenderer* extraLargeRectanglesRenderer)
{
	auto extraLargeRect = extraLargeRectanglesRenderer->CreateObject();
	Objects.push_back(extraLargeRect);

	auto x = 5.3 + 3.2f;
	auto y = 9.5f;
	auto z = 0.0f;

	auto fallShape(new btBoxShape(btVector3(btScalar(0.15), btScalar(1.65), btScalar(0.5))));
	auto fallMotionState(new SceneObjectMotionState(extraLargeRect, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	PhysicsSimulationEngine.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
}

void Level::InitialiseAmmo(SceneObjectRenderer* ammoRenderer)
{
	auto newAmmo = ammoRenderer->CreateObject();
	this->Objects.push_back(newAmmo);

	auto x = 17.25f;
	auto y = 4.50f;
	auto z = 0.0f;

	std::array<btVector3, 3> EggPositions;
	EggPositions[0] = btVector3(0, 0.25, 0);
	EggPositions[1] = btVector3(0, 1, 0);
	EggPositions[2] = btVector3(0, 1.25, 0);

	std::array<btScalar, 3> PartsRadiuses;
	PartsRadiuses[0] = btScalar(.5f);
	PartsRadiuses[1] = btScalar(.25f);
	PartsRadiuses[2] = btScalar(.125f);

	auto eggAmmoShape(new btMultiSphereShape(EggPositions.data(), PartsRadiuses.data(), 3));
	btMotionState* fallMotionState(new SceneObjectMotionState(newAmmo, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btScalar mass = 1.5f;
	btVector3 fallInertia(0, 0, 0);
	eggAmmoShape->calculateLocalInertia(mass, fallInertia);
	PhysicsSimulationEngine.AddPhysicalObject(eggAmmoShape, fallMotionState, mass, fallInertia);
}

void Level::ReinitialiseAmmo(SceneObjectRenderer* ammoRenderer)
{
	this->Objects.pop_back();

	std::unique_ptr<btCollisionObject> objectToDelete(PhysicsSimulationEngine.DynamicsWorld->getCollisionObjectArray()[PhysicsSimulationEngine.DynamicsWorld->getCollisionObjectArray().size() - 1]);
	PhysicsSimulationEngine.DynamicsWorld->removeCollisionObject(objectToDelete.get());
	
	PhysicsSimulationEngine.RigidBodies.at(PhysicsSimulationEngine.RigidBodies.size() - 1).release();
	PhysicsSimulationEngine.RigidBodies.pop_back();
	PhysicsSimulationEngine.ObjectsCollisionShapes.at(PhysicsSimulationEngine.ObjectsCollisionShapes.size() - 1).release();
	PhysicsSimulationEngine.ObjectsCollisionShapes.pop_back();
	PhysicsSimulationEngine.ObjectsMotionStates.at(PhysicsSimulationEngine.ObjectsMotionStates.size() - 1).release();
	PhysicsSimulationEngine.ObjectsMotionStates.pop_back();
	////
	auto newAmmo = ammoRenderer->CreateObject();
	this->Objects.push_back(newAmmo);

	auto x = 17.25f;
	auto y = 4.50f;
	auto z = 0.0f;

	std::array<btVector3, 3> EggPositions;
	EggPositions[0] = btVector3(0, 0.25, 0);
	EggPositions[1] = btVector3(0, 1, 0);
	EggPositions[2] = btVector3(0, 1.25, 0);

	std::array<btScalar, 3> PartsRadiuses;
	PartsRadiuses[0] = btScalar(.5f);
	PartsRadiuses[1] = btScalar(.25f);
	PartsRadiuses[2] = btScalar(.125f);

	auto eggAmmoShape(new btMultiSphereShape(EggPositions.data(), PartsRadiuses.data(), 3));
	auto fallMotionState(new SceneObjectMotionState(newAmmo, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btScalar mass = 1.5f;
	btVector3 fallInertia(0, 0, 0);
	eggAmmoShape->calculateLocalInertia(mass, fallInertia);
	PhysicsSimulationEngine.AddPhysicalObject(eggAmmoShape, fallMotionState, mass, fallInertia);
}

void Level::InitialiseVillains(SceneObjectRenderer* renderer)
{
	auto villain_1 = renderer->CreateObject();
	Objects.push_back(villain_1);

	auto x = -10.0f;
	auto y = 15.0f;
	auto z = 0.0f;

	auto villainfallShape_1(new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5))));
	auto villainMotionState_1(new SceneObjectMotionState(villain_1, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btScalar mass = 1;
	btVector3 fallInertia_1(0, 0, 0);
	villainfallShape_1->calculateLocalInertia(mass, fallInertia_1);
	PhysicsSimulationEngine.AddPhysicalObject(villainfallShape_1, villainMotionState_1, mass, fallInertia_1);
	/////
	auto villain_2 = renderer->CreateObject();
	Objects.push_back(villain_2);

	x = 5.3f + 2.0f;
	y = 9.5f;
	z = 0.0f;

	auto villainfallShape_2(new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5))));
	auto villainMotionState_2(new SceneObjectMotionState(villain_2, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btVector3 fallInertia_2(0, 0, 0);
	villainfallShape_2->calculateLocalInertia(mass, fallInertia_2);
	PhysicsSimulationEngine.AddPhysicalObject(villainfallShape_2, villainMotionState_2, mass, fallInertia_2);
}

void Level::InitialiseBoxes(SceneObjectRenderer* renderer)
{
	auto box_1 = renderer->CreateObject();
	Objects.push_back(box_1);

	auto x = -6.0f;
	auto y = 15.0f;
	auto z = 0.0f;

	auto boxfallShape_1(new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5))));
	auto boxMotionState_1(new SceneObjectMotionState(box_1, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btScalar mass = 1;
	btVector3 fallInertia_1(0, 0, 0);
	boxfallShape_1->calculateLocalInertia(mass, fallInertia_1);
	PhysicsSimulationEngine.AddPhysicalObject(boxfallShape_1, boxMotionState_1, mass, fallInertia_1);
	////
	auto box_2 = renderer->CreateObject();
	Objects.push_back(box_2);

	x = -6.0f;
	y = 16.0f;
	z = 0.0f;

	auto boxfallShape_2(new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5))));
	auto boxMotionState_2(new SceneObjectMotionState(box_2, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btVector3 fallInertia_2(0, 0, 0);
	boxfallShape_2->calculateLocalInertia(mass, fallInertia_2);
	PhysicsSimulationEngine.AddPhysicalObject(boxfallShape_2, boxMotionState_2, mass, fallInertia_2);
	/////
	auto box_3 = renderer->CreateObject();
	Objects.push_back(box_3);

	x = -6.0f;
	y = 17.0f;
	z = 0.0f;

	auto boxfallShape_3(new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5))));
	auto boxMotionState_3(new SceneObjectMotionState(box_3, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btVector3 fallInertia_3(0, 0, 0);
	boxfallShape_3->calculateLocalInertia(mass, fallInertia_3);
	PhysicsSimulationEngine.AddPhysicalObject(boxfallShape_3, boxMotionState_3, mass, fallInertia_3);
	//////
	auto box_4 = renderer->CreateObject();
	Objects.push_back(box_4);

	x = -7.0f;
	y = 15.0f;
	z = 0.0f;

	auto boxfallShape_4(new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5))));
	auto boxMotionState_4(new SceneObjectMotionState(box_4, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btVector3 fallInertia_4(0, 0, 0);
	boxfallShape_4->calculateLocalInertia(mass, fallInertia_4);
	PhysicsSimulationEngine.AddPhysicalObject(boxfallShape_4, boxMotionState_4, mass, fallInertia_4);
	/////////
	auto box_5 = renderer->CreateObject();
	Objects.push_back(box_5);

	x = -7.0f;
	y = 16.0f;
	z = 0.0f;

	auto boxfallShape_5(new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5))));
	auto boxMotionState_5(new SceneObjectMotionState(box_5, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btVector3 fallInertia_5(0, 0, 0);
	boxfallShape_5->calculateLocalInertia(mass, fallInertia_5);
	PhysicsSimulationEngine.AddPhysicalObject(boxfallShape_5, boxMotionState_5, mass, fallInertia_5);
	/////////
	auto box_6 = renderer->CreateObject();
	Objects.push_back(box_6);

	x = -8.0f;
	y = 15.0f;
	z = 0.0f;

	auto boxfallShape_6(new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5))));
	auto boxMotionState_6(new SceneObjectMotionState(box_6, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btVector3 fallInertia_6(0, 0, 0);
	boxfallShape_6->calculateLocalInertia(mass, fallInertia_6);
	PhysicsSimulationEngine.AddPhysicalObject(boxfallShape_6, boxMotionState_6, mass, fallInertia_6);
}

void Level::InitialiseTerrain()
{
	auto x = -8.25f;
	auto y = 14.50f;
	auto z = 0.0f;

	auto fallShape_1(new btBoxShape(btVector3(btScalar(2.50f), btScalar(.50f), btScalar(2.50f))));
	auto fallMotionState_1(new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btScalar mass = 0.0f;
	btVector3 fallInertia_1(0, 0, 0);
	fallShape_1->calculateLocalInertia(mass, fallInertia_1);
	PhysicsSimulationEngine.AddPhysicalObject(fallShape_1, fallMotionState_1, mass, fallInertia_1);
	///////////
	x = 17.25f;
	y = 4.50f;
	z = 0.0f;

	auto fallShape_2(new btBoxShape(btVector3(btScalar(2.50f), btScalar(.50f), btScalar(2.50f))));
	auto fallMotionState_2(new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btVector3 fallInertia_2(0, 0, 0);
	fallShape_2->calculateLocalInertia(mass, fallInertia_2);
	PhysicsSimulationEngine.AddPhysicalObject(fallShape_2, fallMotionState_2, mass, fallInertia_2);
	/////
	x = 7.25f;
	y = 9.50f;
	z = 0.0f;

	auto fallShape(new btBoxShape(btVector3(btScalar(4.0f), btScalar(.50f), btScalar(3.0f))));
	auto fallMotionState(new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z))));
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	PhysicsSimulationEngine.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
}

void Level::Kick()
{
	PhysicsSimulationEngine.RigidBodies.at(PhysicsSimulationEngine.RigidBodies.size()-1)->applyImpulse(btVector3(0, 0.f, 1), btVector3(0.5, -0.2, 0));
}

void Level::Left()
{
	PhysicsSimulationEngine.RigidBodies.at(PhysicsSimulationEngine.RigidBodies.size() - 1)->applyImpulse(btVector3(1.0f, 0, -.0f), btVector3(0, 1.5f, 0));
}

void Level::Right()
{
	PhysicsSimulationEngine.RigidBodies.at(PhysicsSimulationEngine.RigidBodies.size() - 1)->applyImpulse(btVector3(-1.0f, 0, .0f), btVector3(0.5, 0, 0));
}

void Level::Back()
{
	PhysicsSimulationEngine.RigidBodies.at(PhysicsSimulationEngine.RigidBodies.size() - 1)->applyImpulse(btVector3(-.0f, -0.0f, -1.0), btVector3(0.5, 0, 0));
}

void Level::Punch()
{
	PhysicsSimulationEngine.RigidBodies.at(PhysicsSimulationEngine.RigidBodies.size() - 1)->applyImpulse(btVector3(.0f, 1, 0), btVector3(0.5f, 0, 0));
}

void Level::Update()
{
	
	//Управление мышью
	if (this->Objects.at(Objects.size() - 1)->deltaX > 0.0f ||
		this->Objects.at(Objects.size() - 1)->deltaY > 0.0f)
	{
		PhysicsSimulationEngine.RigidBodies.at(PhysicsSimulationEngine.RigidBodies.size() - 1)->applyImpulse(btVector3(this->Objects.at(Objects.size() - 1)->deltaX / 100, this->Objects.at(Objects.size() - 1)->deltaY / 100, 0), btVector3(0.f, 1.5f, 0));

		this->Objects.at(Objects.size() - 1)->deltaX = 0.0f;
		this->Objects.at(Objects.size() - 1)->deltaY = 0.0f;
	}
	//Удаление улетевших снарядов
	auto ammoPosition = PhysicsSimulationEngine.RigidBodies.at(PhysicsSimulationEngine.RigidBodies.size() - 1)->getCenterOfMassPosition();
	
	if (ammoPosition.getX() <= -33.0f)
		IsAmmoLost = true;

	//Удаление разрушеных целей //Разрушаемость - не решена
	//if (PhysicsSimulationEngine.IsDestroyed && PhysicsSimulationEngine.TickCount == 0)
	//{
	//	short index = PhysicsSimulationEngine.DestroyedIndex;
	//	objToDelete = PhysicsSimulationEngine.DestroyedIndex;
	//	objQuantity = PhysicsSimulationEngine.DynamicsWorld->getCollisionObjectArray().size();
	//	this->Objects.erase(Objects.end() - index);

	//	/*CubeMotionState* Obj = (CubeMotionState*)this->PhysicsSimulationEngine.Obj;
	//	auto t = Obj->getObj();*/

	//	//this->targetRenderer->Spheres.erase(targetRenderer->Spheres.end() + PhysicsSimulationEngine.DestroyedIndex);

	//	int pos = PhysicsSimulationEngine.DynamicsWorld->getCollisionObjectArray().size() - (index);

	//	btCollisionObject* obj = PhysicsSimulationEngine.DynamicsWorld->getCollisionObjectArray()[pos];
	//	PhysicsSimulationEngine.DynamicsWorld->removeCollisionObject(obj);
	//	delete obj;

	//	PhysicsSimulationEngine.RigidBodies.at(PhysicsSimulationEngine.RigidBodies.size() - (index )).release();
	//	PhysicsSimulationEngine.RigidBodies.erase(PhysicsSimulationEngine.RigidBodies.end() - (index ));
	//	PhysicsSimulationEngine.ObjectsCollisionShapes.at(PhysicsSimulationEngine.ObjectsCollisionShapes.size() - (index )).release();
	//	PhysicsSimulationEngine.ObjectsCollisionShapes.erase(PhysicsSimulationEngine.ObjectsCollisionShapes.end() - (index ));
	//	PhysicsSimulationEngine.ObjectsMotionStates.at(PhysicsSimulationEngine.ObjectsMotionStates.size() - (index )).release();
	//	PhysicsSimulationEngine.ObjectsMotionStates.erase(PhysicsSimulationEngine.ObjectsMotionStates.end() - (index ));

	//	PhysicsSimulationEngine.IsDestroyed = false;
	//}

	PhysicsSimulationEngine.Update();

}

Level::~Level(void)
{
}
