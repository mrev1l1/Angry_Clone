#include "pch.h"
#include "Level.h"
#include "CubeMotionState.h"
#include "PseudoSphereMotionState.h"
#include "AmmoMotionState.h"
#include "ModelFileHandler.h"
#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h";

vector<btVector3>* Vertices;
vector<unsigned short>* Indices;
Level::Level(void) : IsAmmoLost(false)
{
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	auto groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

	m_physics.AddPhysicalObject(groundShape, groundMotionState, 0, btVector3(0, 0, 0));

	//btTriangleMesh* AmmoPlatform = new btTriangleMesh();// numTriangles, triangleIndexBase, triangleIndexStride, numVertices, vertexBase, vertexStride);

	//ModelFileHandler* AmmoPlatformModel = new ModelFileHandler("C:\\Users\\Îëåêñàíäð\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\rock2.txt", true);
	//vector<btVector3>* AmmoPlatformVertices = AmmoPlatformModel->getVerticesVeñtor();
	//vector<unsigned short>* AmmoPlatformIndices = AmmoPlatformModel->getIndicesVector();

	//for (int i = 0; i < AmmoPlatformIndices->size(); i += 3)
	//{
	//	AmmoPlatform->addTriangle(AmmoPlatformVertices->at(AmmoPlatformIndices->at(i)), AmmoPlatformVertices->at(AmmoPlatformIndices->at(i + 1)), AmmoPlatformVertices->at(AmmoPlatformIndices->at(i + 2)));
	//}

	//btConvexShape* AmmoPlatformMesh = new btConvexTriangleMeshShape(AmmoPlatform);
	//btDefaultMotionState* AmmoPlatformMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-15.0f, 0.0f, -2.5f)));

	//m_physics.AddPhysicalObject(AmmoPlatformMesh, AmmoPlatformMotionState, 0, btVector3(0, 0, 0));
/////////////////
//	btTriangleMesh* FirstPlatform = new btTriangleMesh();// numTriangles, triangleIndexBase, triangleIndexStride, numVertices, vertexBase, vertexStride);
//
//	ModelFileHandler* FirstPlatformModel = new ModelFileHandler("C:\\Users\\Îëåêñàíäð\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\optimizedTerrain\\platform1.txt", true);
//	vector<btVector3>* FirstPlatformVertices = FirstPlatformModel->getVerticesVeñtor();
//	vector<unsigned short>* FirstPlatformIndices = FirstPlatformModel->getIndicesVector();
//
//	for (int i = 0; i < FirstPlatformIndices->size(); i += 3)
//	{
//		FirstPlatform->addTriangle(FirstPlatformVertices->at(FirstPlatformIndices->at(i)), FirstPlatformVertices->at(FirstPlatformIndices->at(i + 1)), FirstPlatformVertices->at(FirstPlatformIndices->at(i + 2)));
//	}
//
//	btConvexShape* FirstPlatformMesh = new btConvexTriangleMeshShape(FirstPlatform);
//	btDefaultMotionState* FirstPlatformMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-5.1945, 8.6645, -11.203)));
//
//	m_physics.AddPhysicalObject(FirstPlatformMesh, FirstPlatformMotionState, 0, btVector3(0, 0, 0));
//	///////////////
//	btTriangleMesh* SecondPlatform = new btTriangleMesh();// numTriangles, triangleIndexBase, triangleIndexStride, numVertices, vertexBase, vertexStride);
//
//	ModelFileHandler* SecondPlatformModel = new ModelFileHandler("C:\\Users\\Îëåêñàíäð\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\optimizedTerrain\\platform1.txt", true);
//	vector<btVector3>* SecondPlatformVertices = SecondPlatformModel->getVerticesVeñtor();
//	vector<unsigned short>* SecondPlatformIndices = SecondPlatformModel->getIndicesVector();
//
//	for (int i = 0; i < SecondPlatformIndices->size(); i += 3)
//	{
//		SecondPlatform->addTriangle(SecondPlatformVertices->at(SecondPlatformIndices->at(i)), SecondPlatformVertices->at(SecondPlatformIndices->at(i + 1)), SecondPlatformVertices->at(SecondPlatformIndices->at(i + 2)));
//	}
//
//	btConvexShape* SecondPlatformMesh = new btConvexTriangleMeshShape(SecondPlatform);
//	btDefaultMotionState* SecondPlatformMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-11.711, 8.4095, -4.64)));
//
//	m_physics.AddPhysicalObject(SecondPlatformMesh, SecondPlatformMotionState, 0, btVector3(0, 0, 0));
}

void Level::InitialiseSmallRectangles(MyRenderer* smallRectanglesRenderer)
{
	auto smallRect = smallRectanglesRenderer->CreateObject();
	m_cubes.push_back(smallRect);

	auto x = 5.3f;
	auto y = 9.5f ;
	auto z = 0.0f;

	auto fallShape = new btBoxShape(btVector3(btScalar(0.15), btScalar(0.5), btScalar(0.5)));
	btMotionState* fallMotionState = new CubeMotionState(smallRect, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	m_physics.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
	///
	auto smallRect_1 = smallRectanglesRenderer->CreateObject();
	m_cubes.push_back(smallRect_1);

	x = 5.3f;
	y = 11.5f;
	z = 0.0f;

	 auto fallShape_1 = new btBoxShape(btVector3(btScalar(0.15), btScalar(0.5), btScalar(0.5)));
	 btMotionState* fallMotionState_1 = new CubeMotionState(smallRect_1, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass_1 = 1;
	btVector3 fallInertia_1(0, 0, 0);
	fallShape_1->calculateLocalInertia(mass_1, fallInertia_1);
	m_physics.AddPhysicalObject(fallShape_1, fallMotionState_1, mass_1, fallInertia_1);
	//////
	auto smallRect2 = smallRectanglesRenderer->CreateObject();
	m_cubes.push_back(smallRect2);

	 x = 6.6f;
	 y = 9.5f + 2.3f;
	 z = 0.0f;

	auto fallShape2 = new btBoxShape(btVector3(btScalar(0.15), btScalar(0.5), btScalar(0.5)));
	btMotionState* fallMotionState2 = new CubeMotionState(smallRect2, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass2 = 1;
	btVector3 fallInertia2(0, 0, 0);
	fallShape2->calculateLocalInertia(mass2, fallInertia2);
	m_physics.AddPhysicalObject(fallShape2, fallMotionState2, mass2, fallInertia2);
}

void Level::InitialiseNormalRectangles(MyRenderer* normallRectanglesRenderer)
{
	auto normallRect = normallRectanglesRenderer->CreateObject();
	m_cubes.push_back(normallRect);

	auto x = 6.3f;
	auto y = 9.5f;
	auto z = 0.0f;

	auto fallShape = new btBoxShape(btVector3(btScalar(0.15), btScalar(1.0), btScalar(0.5)));
	btMotionState* fallMotionState = new CubeMotionState(normallRect, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	m_physics.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
}

void Level::InitialiseLargeRectangles(MyRenderer* largeRectanglesRenderer)
{
	auto largeRect = largeRectanglesRenderer->CreateObject();
	m_cubes.push_back(largeRect);

	auto x =  5.3f;
	auto y = 11.5f;
	auto z = 0.0f;

	auto fallShape = new btBoxShape(btVector3(btScalar(1.5), btScalar(0.15), btScalar(0.5)));
	btMotionState* fallMotionState = new CubeMotionState(largeRect, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	m_physics.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
	/////
	auto largeRect1 = largeRectanglesRenderer->CreateObject();
	m_cubes.push_back(largeRect1);

	 x = 6.6+1.4f;
	 y = 9.5 + 3.3f ;
	 z = 0.0f;

	auto fallShape1 = new btBoxShape(btVector3(btScalar(1.5), btScalar(0.15), btScalar(0.5)));
	btMotionState* fallMotionState1 = new CubeMotionState(largeRect1, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass1 = 1;
	btVector3 fallInertia1(0, 0, 0);
	fallShape1->calculateLocalInertia(mass1, fallInertia1);
	m_physics.AddPhysicalObject(fallShape1, fallMotionState1, mass1, fallInertia1);
}

void Level::InitialiseExtraLargeRectangles(MyRenderer* extraLargeRectanglesRenderer)
{
	auto extraLargeRect = extraLargeRectanglesRenderer->CreateObject();
	m_cubes.push_back(extraLargeRect);

	auto x = 5.3 + 3.2f;
	auto y = 9.5f;
	auto z = 0.0f;

	auto fallShape = new btBoxShape(btVector3(btScalar(0.15), btScalar(1.65), btScalar(0.5)));
	btMotionState* fallMotionState = new CubeMotionState(extraLargeRect, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	m_physics.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
}

void Level::InitialiseAmmo(MyRenderer* ammoRenderer)
{
	auto newAmmo = ammoRenderer->CreateObject();
	this->m_cubes.push_back(newAmmo);

	auto x = 17.25f;
	auto y = 4.50f;
	auto z = 0.0f;

	btVector3* EggPositions = new btVector3[3];
	/*EggPositions[0] = btVector3(0, 0.0, 0);*/
	EggPositions[0] = btVector3(0, 0.25, 0);
	EggPositions[1] = btVector3(0, 1, 0);
	EggPositions[2] = btVector3(0, 1.25, 0);

	btScalar* PartsRadiuses = new btScalar[3];
	/*PartsRadiuses[0] = btScalar(1);new btScalar[3];*/
	PartsRadiuses[0] = btScalar(.5f);
	PartsRadiuses[1] = btScalar(.25f);
	PartsRadiuses[2] = btScalar(.125f);

	btMultiSphereShape* eggAmmoShape = new btMultiSphereShape(EggPositions, PartsRadiuses, 3);
	btMotionState* fallMotionState = new CubeMotionState(newAmmo, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass = 1.5f;
	btVector3 fallInertia(0, 0, 0);
	eggAmmoShape->calculateLocalInertia(mass, fallInertia);
	m_physics.AddPhysicalObject(eggAmmoShape, fallMotionState, mass, fallInertia);
	auto p = eggAmmoShape->getSpherePosition(0);
}

void Level::ReinitialiseAmmo(MyRenderer* ammoRenderer)
{
	this->m_cubes.pop_back();
	//ammoRenderer->Objects.pop_back();

	auto pos = m_physics.m_dynamicsWorld->getCollisionObjectArray();
	btCollisionObject* obj = m_physics.m_dynamicsWorld->getCollisionObjectArray()[m_physics.m_dynamicsWorld->getCollisionObjectArray().size() - 1];
	m_physics.m_dynamicsWorld->removeCollisionObject(obj);
	delete obj;
	
	m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1).release();
	m_physics.m_rigidBodies.pop_back();
	m_physics.m_shapes.at(m_physics.m_shapes.size() - 1).release();
	m_physics.m_shapes.pop_back();
	m_physics.states.at(m_physics.states.size() - 1).release();
	m_physics.states.pop_back();
	////
	auto newAmmo = ammoRenderer->CreateObject();
	this->m_cubes.push_back(newAmmo);

	auto x = 17.25f;
	auto y = 4.50f;
	auto z = 0.0f;

	btVector3* EggPositions = new btVector3[3];
	EggPositions[0] = btVector3(0, 0.25, 0);
	EggPositions[1] = btVector3(0, 1, 0);
	EggPositions[2] = btVector3(0, 1.25, 0);

	btScalar* PartsRadiuses = new btScalar[3];
	PartsRadiuses[0] = btScalar(.5f);
	PartsRadiuses[1] = btScalar(.25f);
	PartsRadiuses[2] = btScalar(.125f);

	btMultiSphereShape* eggAmmoShape = new btMultiSphereShape(EggPositions, PartsRadiuses, 3);
	btMotionState* fallMotionState = new CubeMotionState(newAmmo, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass = 1.5f;
	btVector3 fallInertia(0, 0, 0);
	eggAmmoShape->calculateLocalInertia(mass, fallInertia);
	m_physics.AddPhysicalObject(eggAmmoShape, fallMotionState, mass, fallInertia);
	auto p = eggAmmoShape->getSpherePosition(0);
}

void fillTriangleMesh(btTriangleMesh* item, char* filename)
{
	ModelFileHandler modelReader(filename, true);

	vector<btVector3>* verticesPtr = modelReader.getVerticesVeñtor();
	vector<unsigned short>* indicesPtr = modelReader.getIndicesVector();
	for (int i = 0; i < indicesPtr->size() / 3; i += 3)
	{
		item->addTriangle(verticesPtr->at(indicesPtr->at(i)), verticesPtr->at(indicesPtr->at(i + 1)), verticesPtr->at(indicesPtr->at(i + 2)), false);
	}

}

void Level::InitialiseCubes(MyRenderer* cubesRenderer)
{
	//auto cube = cubesRenderer->CreateCube();
	//m_cubes.push_back(cube);

	//auto x = 6.0f;
	//auto y = 20 + 0.0f;
	//auto z = 0.0f;

	//auto fallShape = new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5)));
	//btMotionState* fallMotionState = new CubeMotionState(cube, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	//btScalar mass = 1;
	//btVector3 fallInertia(0, 0, 0);
	//fallShape->calculateLocalInertia(mass, fallInertia);
	//m_physics.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
	/////
	//auto cube1 = cubesRenderer->CreateCube();
	//m_cubes.push_back(cube1);

	// x = 7.0f;
	// y = 20 + 0.0f;
	// z = 0.0f;

	//auto fallShape1 = new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5)));
	//btMotionState* fallMotionState1 = new CubeMotionState(cube1, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	//btScalar mass1 = 1;
	//btVector3 fallInertia1(0, 0, 0);
	//fallShape1->calculateLocalInertia(mass1, fallInertia1);
	//m_physics.AddPhysicalObject(fallShape1, fallMotionState1, mass1, fallInertia1);
	//////
	//auto cube2 = cubesRenderer->CreateCube();
	//m_cubes.push_back(cube2);

	// x = 8.0f;
	// y = 20 + 0.0f;
	// z = 0.0f;

	//auto fallShape2 = new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5)));
	//btMotionState* fallMotionState2 = new CubeMotionState(cube2, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	//btScalar mass2 = 1;
	//btVector3 fallInertia2(0, 0, 0);
	//fallShape2->calculateLocalInertia(mass2, fallInertia2);
	//m_physics.AddPhysicalObject(fallShape2, fallMotionState2, mass2, fallInertia2);
	////////
	//auto cube3 = cubesRenderer->CreateCube();
	//m_cubes.push_back(cube3);

	// x = 6.0f;
	// y = 20 + 1.0f;
	// z = 0.0f;

	//auto fallShape3 = new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5)));
	//btMotionState* fallMotionState3 = new CubeMotionState(cube3, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	//btScalar mass3 = 1;
	//btVector3 fallInertia3(0, 0, 0);
	//fallShape3->calculateLocalInertia(mass3, fallInertia3);
	//m_physics.AddPhysicalObject(fallShape3, fallMotionState3, mass3, fallInertia3);
	//////
	//auto cube4 = cubesRenderer->CreateCube();
	//m_cubes.push_back(cube4);

	// x = 7.0f;
	// y = 20 + 1.0f;
	// z = 0.0f;

	//auto fallShape4 = new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5)));
	//btMotionState* fallMotionState4 = new CubeMotionState(cube4, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	//btScalar mass4 = 1;
	//btVector3 fallInertia4(0, 0, 0);
	//fallShape4->calculateLocalInertia(mass4, fallInertia4);
	//m_physics.AddPhysicalObject(fallShape4, fallMotionState4, mass4, fallInertia4);
	/////
	//auto cube5 = cubesRenderer->CreateCube();
	//m_cubes.push_back(cube5);

	// x = 6.0f;
	// y = 20 + 2.0f;
	// z = 0.0f;

	//auto fallShape5 = new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5)));
	//btMotionState* fallMotionState5 = new CubeMotionState(cube5, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	//btScalar mass5 = 1;
	//btVector3 fallInertia5(0, 0, 0);
	//fallShape5->calculateLocalInertia(mass5, fallInertia5);
	//m_physics.AddPhysicalObject(fallShape5, fallMotionState5, mass5, fallInertia5);
}

void Level::InitialiseVillains(MyRenderer* renderer)
{
	auto villain1 = renderer->CreateObject();
	m_cubes.push_back(villain1);

	auto x = -10.0f;
	auto y = 15.0f;
	auto z = 0.0f;

	auto villain1fallShape = new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5)));
	btMotionState* villain1MotionState = new CubeMotionState(villain1, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass1 = 1;
	btVector3 fallInertia1(0, 0, 0);
	villain1fallShape->calculateLocalInertia(mass1, fallInertia1);
	m_physics.AddPhysicalObject(villain1fallShape, villain1MotionState, mass1, fallInertia1);
	/////
	auto villain2 = renderer->CreateObject();
	m_cubes.push_back(villain2);

	x = 5.3f + 2.0f;
	y = 9.5f;
	z = 0.0f;

	auto villain2fallShape = new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5)));
	btMotionState* villain2MotionState = new CubeMotionState(villain2, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	mass1 = 1;
	btVector3 fallInertia2(0, 0, 0);
	villain1fallShape->calculateLocalInertia(mass1, fallInertia2);
	m_physics.AddPhysicalObject(villain2fallShape, villain2MotionState, mass1, fallInertia2);
}

void Level::InitialiseBoxes(MyRenderer* renderer)
{
	auto box1 = renderer->CreateObject();
	m_cubes.push_back(box1);

	auto x = -6.0f;
	auto y = 15.0f;
	auto z = 0.0f;

	auto box1fallShape = new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5)));
	btMotionState* box1MotionState = new CubeMotionState(box1, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass1 = 1;
	btVector3 fallInertia1(0, 0, 0);
	box1fallShape->calculateLocalInertia(mass1, fallInertia1);
	m_physics.AddPhysicalObject(box1fallShape, box1MotionState, mass1, fallInertia1);
	////
	auto box2 = renderer->CreateObject();
	m_cubes.push_back(box2);

	x = -6.0f;
	y = 16.0f;
	z = 0.0f;

	auto box2fallShape = new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5)));
	btMotionState* box2MotionState = new CubeMotionState(box2, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass2 = 1;
	btVector3 fallInertia2(0, 0, 0);
	box2fallShape->calculateLocalInertia(mass2, fallInertia2);
	m_physics.AddPhysicalObject(box2fallShape, box2MotionState, mass2, fallInertia2);
	/////
	auto box3 = renderer->CreateObject();
	m_cubes.push_back(box3);

	x = -6.0f;
	y = 17.0f;
	z = 0.0f;

	auto box3fallShape = new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5)));
	btMotionState* box3MotionState = new CubeMotionState(box3, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass3 = 1;
	btVector3 fallInertia3(0, 0, 0);
	box3fallShape->calculateLocalInertia(mass3, fallInertia3);
	m_physics.AddPhysicalObject(box3fallShape, box3MotionState, mass3, fallInertia3);
	//////
	auto box4 = renderer->CreateObject();
	m_cubes.push_back(box4);

	x = -7.0f;
	y = 15.0f;
	z = 0.0f;

	auto box4fallShape = new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5)));
	btMotionState* box4MotionState = new CubeMotionState(box4, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass4 = 1;
	btVector3 fallInertia4(0, 0, 0);
	box4fallShape->calculateLocalInertia(mass3, fallInertia4);
	m_physics.AddPhysicalObject(box4fallShape, box4MotionState, mass4, fallInertia4);
	/////////
	auto box5 = renderer->CreateObject();
	m_cubes.push_back(box5);

	x = -7.0f;
	y = 16.0f;
	z = 0.0f;

	auto box5fallShape = new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5)));
	btMotionState* box5MotionState = new CubeMotionState(box5, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass5 = 1;
	btVector3 fallInertia5(0, 0, 0);
	box5fallShape->calculateLocalInertia(mass5, fallInertia5);
	m_physics.AddPhysicalObject(box5fallShape, box5MotionState, mass5, fallInertia5);
	/////////
	auto box6 = renderer->CreateObject();
	m_cubes.push_back(box6);

	x = -8.0f;
	y = 15.0f;
	z = 0.0f;

	auto box6fallShape = new btBoxShape(btVector3(btScalar(0.5), btScalar(0.5), btScalar(0.5)));
	btMotionState* box6MotionState = new CubeMotionState(box6, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass6 = 1;
	btVector3 fallInertia6(0, 0, 0);
	box6fallShape->calculateLocalInertia(mass6, fallInertia6);
	m_physics.AddPhysicalObject(box6fallShape, box6MotionState, mass6, fallInertia6);
}

void Level::InitialiseTerrain(ExtraLargeRectangleRenderer* cubeRenderer)
{
	auto smallRect = cubeRenderer->CreateRectangle();
	m_cubes.push_back(smallRect);

	auto x = 7.25f;
	auto y = 9.50f;
	auto z = 0.0f;

	auto fallShape = new btBoxShape(btVector3(btScalar(4.0f), btScalar(.50f), btScalar(3.0f)));
	btMotionState* fallMotionState = new CubeMotionState(smallRect, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass = 0.0f;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	m_physics.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
}

void Level::InitialiseTerrain()
{
	auto x = -8.25f;
	auto y = 14.50f;
	auto z = 0.0f;

	auto fallShape1 = new btBoxShape(btVector3(btScalar(2.50f), btScalar(.50f), btScalar(2.50f)));
	btMotionState* fallMotionState1 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass = 0.0f;
	btVector3 fallInertia1(0, 0, 0);
	fallShape1->calculateLocalInertia(mass, fallInertia1);
	m_physics.AddPhysicalObject(fallShape1, fallMotionState1, mass, fallInertia1);
	///////////
	x = 17.25f;
	y = 4.50f;
	z = 0.0f;

	auto fallShape2 = new btBoxShape(btVector3(btScalar(2.50f), btScalar(.50f), btScalar(2.50f)));
	btMotionState* fallMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btVector3 fallInertia2(0, 0, 0);
	fallShape1->calculateLocalInertia(mass, fallInertia2);
	m_physics.AddPhysicalObject(fallShape2, fallMotionState2, mass, fallInertia2);
	/////
	x = 7.25f;
	y = 9.50f;
	z = 0.0f;

	auto fallShape = new btBoxShape(btVector3(btScalar(4.0f), btScalar(.50f), btScalar(3.0f)));
	btMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	m_physics.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
}

void Level::Initialise(PseudoSphereRenderer* sphereRenderer)
{
	/*btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	auto groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	m_physics.AddPhysicalObject(groundShape, groundMotionState, 0, btVector3(0, 0, 0));

	this->targetRenderer = sphereRenderer;
	auto pig1 = sphereRenderer->CreatePseudoSphere();
	Enemies.push_back(pig1);

	auto x = 25.7825f;// -18 + .05f;
	auto y = 25;///*1*//*37 + 2.3001f;
	auto z = 17.621f;



	auto fallShape1 = new btSphereShape(btScalar(0.5f));
	btMotionState* fallMotionState1 = new PseudoSphereMotionState(pig1, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass1 = 1;
	btVector3 fallInertia1(0, 0, 0);
	fallShape1->calculateLocalInertia(mass1, fallInertia1);
	m_physics.AddPhysicalObject(fallShape1, fallMotionState1, mass1, fallInertia1);*/
	
	//auto pig2 = sphereRenderer->CreatePseudoSphere();
	//Enemies.push_back(pig2);*/

	//x =  -18 + 2.55f;
	// y = 17 + 0.0f ;
	// z =  0.0f;

	//auto fallShape2 = new btSphereShape(btScalar(0.5f));
	//btMotionState* fallMotionState2 = new PseudoSphereMotionState(pig2, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	//btScalar mass2 = 1;
	//btVector3 fallInertia2(0, 0, 0);
	//fallShape2->calculateLocalInertia(mass2, fallInertia2);
	//m_physics.AddPhysicalObject(fallShape2, fallMotionState2, mass2, fallInertia2);
	//////
	//auto pig3 = sphereRenderer->CreatePseudoSphere();
	//Enemies.push_back(pig3);

	//x =  10.f;
	//y = 20 + 0.0f;
	//z = 0.0f;

	//auto fallShape3 = new btSphereShape(btScalar(0.5f));
	//btMotionState* fallMotionState3 = new PseudoSphereMotionState(pig3, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	//btScalar mass3 = 1;
	//btVector3 fallInertia3(0, 0, 0);
	//fallShape3->calculateLocalInertia(mass3, fallInertia3);
	//m_physics.AddPhysicalObject(fallShape3, fallMotionState3, mass3, fallInertia3);
	////
	
}

void Level::Kick()
{
	auto pos = m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->getCenterOfMassPosition();
	//if (pos.distance(btVector3(0, 0, 0)) > 65)
		//m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->applyImpulse(btVector3(0, -10.5f, 0), btVector3(0.5f, 0, 0));
	m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size()-1)->applyImpulse(btVector3(0, 0.f, 1), btVector3(0.5, -0.2, 0));
}

void Level::Left()
{
	auto pos = m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->getCenterOfMassPosition();
	//if (pos.distance(btVector3(0, 0, 0)) > 65)
		//m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->applyImpulse(btVector3(0, 0, 10.0f), btVector3(0.5f, 0, 0));
	m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->applyImpulse(btVector3(1.0f, 0, -.0f), btVector3(0, 1.5f, 0));
	//m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->applyTorque(m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->getWorldTransform().getBasis() * *(new btVector3(0, 0, 10)));
	
//	this->CurrentAmmo.at(0)->Rotation = 1;
	
}

void Level::Right()
{
	auto pos = m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 2)->getCenterOfMassPosition();
	//if (pos.distance(btVector3(0, 0, 0)) > 65)
		//m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->applyImpulse(btVector3(0, 0, -10.0f), btVector3(0.5f, 0, 0));
	m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->applyImpulse(btVector3(-1.0f, 0, .0f), btVector3(0.5, 0, 0));
}

void Level::Back()
{
	auto pos = m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->getCenterOfMassPosition();
	//if (pos.distance(btVector3(0, 0, 0)) > 65)
		//m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->applyImpulse(btVector3(10.0f, 10.0f, 0), btVector3(0.5f, 0, 0));
	m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->applyImpulse(btVector3(-.0f, -0.0f, -1.0), btVector3(0.5, 0, 0));
}

void Level::Punch()
{
	auto pos = m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->getCenterOfMassPosition();
	//	if (pos.distance(btVector3(0, 0, 0)) > 65)
	//	m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->applyImpulse(btVector3(-22.0f, 0, 0), btVector3(0.5f, 0, 0));
	auto velocity = m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->getVelocityInLocalPoint(btVector3(0.5f, 0, 0));
	m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->applyImpulse(btVector3(.0f, 1, 0), btVector3(0.5f, 0, 0));
}

Level::~Level(void)
{
}

void Level::Update()
{
	
	//Óïðàâëåíèå ìûøüþ
	if (this->m_cubes.at(m_cubes.size() - 1)->deltaX > 0.0f ||
		this->m_cubes.at(m_cubes.size() - 1)->deltaY > 0.0f)
	{
		m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->applyImpulse(btVector3(this->m_cubes.at(m_cubes.size() - 1)->deltaX / 100, this->m_cubes.at(m_cubes.size() - 1)->deltaY / 100, 0), btVector3(0.f, 1.5f, 0));

		this->m_cubes.at(m_cubes.size() - 1)->deltaX = 0.0f;
		this->m_cubes.at(m_cubes.size() - 1)->deltaY = 0.0f;
	}
	//Óäàëåíèå óëåòåâøèõ ñíàðÿäîâ
	auto pos = m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->getCenterOfMassPosition();
	
	if (pos.getX() <= -33.0f)
		IsAmmoLost = true;

	//Óäàëåíèå ðàçðóøåíûõ öåëåé //Ðàçðóøàåìîñòü - íå ðåøåíà
	//if (m_physics.IsDestroyed && m_physics.TickCount == 0)
	//{
	//	short index = m_physics.DestroyedIndex;
	//	objToDelete = m_physics.DestroyedIndex;
	//	objQuantity = m_physics.m_dynamicsWorld->getCollisionObjectArray().size();
	//	this->m_cubes.erase(m_cubes.end() - index);

	//	/*CubeMotionState* Obj = (CubeMotionState*)this->m_physics.Obj;
	//	auto t = Obj->getObj();*/

	//	//this->targetRenderer->Spheres.erase(targetRenderer->Spheres.end() + m_physics.DestroyedIndex);

	//	int pos = m_physics.m_dynamicsWorld->getCollisionObjectArray().size() - (index);

	//	btCollisionObject* obj = m_physics.m_dynamicsWorld->getCollisionObjectArray()[pos];
	//	m_physics.m_dynamicsWorld->removeCollisionObject(obj);
	//	delete obj;

	//	m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - (index )).release();
	//	m_physics.m_rigidBodies.erase(m_physics.m_rigidBodies.end() - (index ));
	//	m_physics.m_shapes.at(m_physics.m_shapes.size() - (index )).release();
	//	m_physics.m_shapes.erase(m_physics.m_shapes.end() - (index ));
	//	m_physics.states.at(m_physics.states.size() - (index )).release();
	//	m_physics.states.erase(m_physics.states.end() - (index ));

	//	m_physics.IsDestroyed = false;
	//}

	m_physics.Update();

}