#include "pch.h"
#include "Level.h"
#include "CubeMotionState.h"
#include "PseudoSphereMotionState.h"
#include "AmmoMotionState.h"
#include "ModelFileHandler.h"
#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h";


Level::Level(void) : IsAmmoLost(false)
{
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	auto groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

	m_physics.AddPhysicalObject(groundShape, groundMotionState, 0, btVector3(0, 0, 0));
	
	//btTriangleMesh* OriginalTriangleMesh  = new btTriangleMesh();// numTriangles, triangleIndexBase, triangleIndexStride, numVertices, vertexBase, vertexStride);
	
	ModelFileHandler* terrainModel = new ModelFileHandler("C:\\Users\\Îëåêñàíäð\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\newTerrain\\Model.txt", true);
	vector<btVector3>* Vertices = terrainModel->getVerticesVeñtor();
	vector<unsigned short>* Indices = terrainModel->getIndicesVector();

	/*for (int i = 0; i < Indices->size(); i+=3)
	{
		OriginalTriangleMesh->addTriangle(Vertices->at(Indices->at(i)), Vertices->at(Indices->at(i+1)), Vertices->at(Indices->at(i+2)));
	}*/

	
	//btConvexShape* NewStaticMesh = new btConvexTriangleMeshShape(OriginalTriangleMesh);
	
	btConvexHullShape* ConvexHull = new btConvexHullShape();
	for (int i = 0; i < Vertices->size(); i++)
	{
		ConvexHull->addPoint(Vertices->at(i));
	}
	btShapeHull* hull = new btShapeHull(ConvexHull);
	btScalar margin = ConvexHull->getMargin();
	hull->buildHull(margin);
	btConvexHullShape* simplifiedConvexShape = new btConvexHullShape(*hull->getVertexPointer(), hull->numVertices());

	btDefaultMotionState* OriginalTriangleMeshMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));

	m_physics.AddPhysicalObject(simplifiedConvexShape, OriginalTriangleMeshMotionState, 0, btVector3(0, 0, 0));
/////////////
//	btTriangleMesh* AmmoPlatform = new btTriangleMesh();// numTriangles, triangleIndexBase, triangleIndexStride, numVertices, vertexBase, vertexStride);
//
//	ModelFileHandler* AmmoPlatformModel = new ModelFileHandler("C:\\Users\\Îëåêñàíäð\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\optimizedTerrain\\ammo_platform.txt", true);
//	vector<btVector3>* AmmoPlatformVertices = AmmoPlatformModel->getVerticesVeñtor();
//	vector<unsigned short>* AmmoPlatformIndices = AmmoPlatformModel->getIndicesVector();
//
//	for (int i = 0; i < AmmoPlatformIndices->size(); i += 3)
//	{
//		AmmoPlatform->addTriangle(AmmoPlatformVertices->at(AmmoPlatformIndices->at(i)), AmmoPlatformVertices->at(AmmoPlatformIndices->at(i + 1)), AmmoPlatformVertices->at(AmmoPlatformIndices->at(i + 2)));
//	}
//
//	btConvexShape* AmmoPlatformMesh = new btConvexTriangleMeshShape(AmmoPlatform);
//	btDefaultMotionState* AmmoPlatformMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-5.881, 8.8085, -20.633)));
//
//	m_physics.AddPhysicalObject(AmmoPlatformMesh, AmmoPlatformMotionState, 0, btVector3(0, 0, 0));
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

void Level::InitialiseSmallRectangles(SmallRectangleRenderer* smallRectanglesRenderer)
{
	auto smallRect = smallRectanglesRenderer->CreateRectangle();
	m_cubes.push_back(smallRect);

	auto x = -18.0f;
	auto y = 17.0f ;
	auto z = 0.0f;

	auto fallShape = new btBoxShape(btVector3(btScalar(0.15), btScalar(0.5), btScalar(0.5)));
	btMotionState* fallMotionState = new CubeMotionState(smallRect, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	m_physics.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
	///
	auto smallRect_1 = smallRectanglesRenderer->CreateRectangle();
	m_cubes.push_back(smallRect_1);

	x =  -18.0f;
	y = 17 + 1.0f ;
	z = 0.0f;

	 auto fallShape_1 = new btBoxShape(btVector3(btScalar(0.15), btScalar(0.5), btScalar(0.5)));
	 btMotionState* fallMotionState_1 = new CubeMotionState(smallRect_1, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass_1 = 1;
	btVector3 fallInertia_1(0, 0, 0);
	fallShape_1->calculateLocalInertia(mass_1, fallInertia_1);
	m_physics.AddPhysicalObject(fallShape_1, fallMotionState_1, mass_1, fallInertia_1);
	////
	auto smallRect2 = smallRectanglesRenderer->CreateRectangle();
	m_cubes.push_back(smallRect2);

	 x = -18 + 1.6f;
	 y = 17 + 2.3f;
	 z = 0.0f;

	auto fallShape2 = new btBoxShape(btVector3(btScalar(0.15), btScalar(0.5), btScalar(0.5)));
	btMotionState* fallMotionState2 = new CubeMotionState(smallRect2, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass2 = 1;
	btVector3 fallInertia2(0, 0, 0);
	fallShape2->calculateLocalInertia(mass2, fallInertia2);
	m_physics.AddPhysicalObject(fallShape2, fallMotionState2, mass2, fallInertia2);
}

void Level::InitialiseNormallRectangles(SmallRectangleRenderer* normallRectanglesRenderer)
{
	auto normallRect = normallRectanglesRenderer->CreateRectangle();
	m_cubes.push_back(normallRect);

	auto x = -18 + 1.0f;
	auto y = 17.0f;
	auto z = 0.0f;

	auto fallShape = new btBoxShape(btVector3(btScalar(0.15), btScalar(1.0), btScalar(0.5)));
	btMotionState* fallMotionState = new CubeMotionState(normallRect, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	m_physics.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
}

void Level::InitialiseNormallRectangles(NormallRectangleRenderer* normallRectanglesRenderer)
{
	auto normallRect = normallRectanglesRenderer->CreateRectangle();
	m_cubes.push_back(normallRect);

	auto x =  -2.0f;
	auto y = 18.0f ;
	auto z = -10.0f;

	auto fallShape = new btBoxShape(btVector3(btScalar(0.15), btScalar(1.0), btScalar(0.5)));
	btMotionState* fallMotionState = new CubeMotionState(normallRect, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	m_physics.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
}

void Level::InitialiseLargeRectangles(LargeRectangleRenderer* largeRectanglesRenderer)
{
	auto largeRect = largeRectanglesRenderer->CreateRectangle();
	m_cubes.push_back(largeRect);

	auto x =  -18 + 0.35f;
	auto y = 17 + 2.0f;
	auto z = 0.0f;

	auto fallShape = new btBoxShape(btVector3(btScalar(1.5), btScalar(0.15), btScalar(0.5)));
	btMotionState* fallMotionState = new CubeMotionState(largeRect, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	m_physics.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
	/////
	auto largeRect1 = largeRectanglesRenderer->CreateRectangle();
	m_cubes.push_back(largeRect1);

	 x = -18 + 3.0f;
	 y = 17 + 3.3f ;
	 z = 0.0f;

	auto fallShape1 = new btBoxShape(btVector3(btScalar(1.5), btScalar(0.15), btScalar(0.5)));
	btMotionState* fallMotionState1 = new CubeMotionState(largeRect1, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass1 = 1;
	btVector3 fallInertia1(0, 0, 0);
	fallShape1->calculateLocalInertia(mass1, fallInertia1);
	m_physics.AddPhysicalObject(fallShape1, fallMotionState1, mass1, fallInertia1);
}

void Level::InitialiseExtraLargeRectangles(MyRenderer* heightMapRenderer)
{
	auto heightMap = heightMapRenderer->CreateHeightMap();
	btTriangleMesh* OriginalTriangleMesh = new btTriangleMesh();// numTriangles, triangleIndexBase, triangleIndexStride, numVertices, vertexBase, vertexStride);

	ModelFileHandler* terrainModel = new ModelFileHandler("C:\\Users\\Îëåêñàíäð\\AppData\\Local\\Packages\\a5f5ffab-88e8-40fd-8e9e-80a2994ded96_kqgv1awp48cbp\\LocalState\\optimizedTerrain\\HM.txt", true);
	vector<btVector3>* Vertices = terrainModel->getVerticesVeñtor();
	vector<unsigned short>* Indices = terrainModel->getIndicesVector();

	for (int i = 0; i < Indices->size(); i += 3)
	{
		OriginalTriangleMesh->addTriangle(Vertices->at(Indices->at(i)), Vertices->at(Indices->at(i + 1)), Vertices->at(Indices->at(i + 2)));
	}


	btConvexShape* NewStaticMesh = new btConvexTriangleMeshShape(OriginalTriangleMesh);

	btMotionState* OriginalTriangleMeshMotionState = new CubeMotionState(heightMap,btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btScalar mass = 0;
	btVector3 fallInertia(0, 0, 0);
	NewStaticMesh->calculateLocalInertia(mass, fallInertia);

	m_physics.AddPhysicalObject(NewStaticMesh, OriginalTriangleMeshMotionState, mass, fallInertia);

	/*auto extraLargeRect = extraLargeRectanglesRenderer->CreateCube();
	m_cubes.push_back(extraLargeRect);

	auto x = -18 + 4.2f;
	auto y = 17 + 0.0f;
	auto z = 0.0f;

	auto fallShape = new btBoxShape(btVector3(btScalar(0.15), btScalar(1.65), btScalar(0.5)));
	btMotionState* fallMotionState = new CubeMotionState(extraLargeRect, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	m_physics.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);*/
}

void Level::InitialiseAmmo(AmmoRenderer* ammoRenderer)
{
	void fillTriangleMesh(btTriangleMesh* item, char* filename);

	auto newAmmo = ammoRenderer->CreateAmmo();
	this->CurrentAmmo.push_back(newAmmo);

	auto x = 0.1625f; 
	auto y = 8.118f;
	auto z = 20.833f;

	btVector3* EggPositions = new btVector3[1];
	EggPositions[0] = btVector3(0, 0.0, 0);
	/*new btVector3[3];
	EggPositions[0] = btVector3(0, 0.25, 0);
	EggPositions[1] = btVector3(0, 1, 0);
	EggPositions[2] = btVector3(0, 1.25, 0);*/

	btScalar* PartsRadiuses = new btScalar[1];
	PartsRadiuses[0] = btScalar(1);/*new btScalar[3];
	PartsRadiuses[0] = btScalar(.5f);
	PartsRadiuses[1] = btScalar(.25f);
	PartsRadiuses[2] = btScalar(.125f);*/

	btMultiSphereShape* eggAmmoShape = new btMultiSphereShape(EggPositions, PartsRadiuses, 1);
	btMotionState* fallMotionState = new AmmoMotionState(newAmmo, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass = 1.5f;
	btVector3 fallInertia(0, 0, 0);
	eggAmmoShape->calculateLocalInertia(mass, fallInertia);
	m_physics.AddPhysicalObject(eggAmmoShape, fallMotionState, mass, fallInertia);
	auto p = eggAmmoShape->getSpherePosition(0);
}

void Level::ReinitialiseAmmo(AmmoRenderer* ammoRenderer)
{
	this->CurrentAmmo.pop_back();
	ammoRenderer->CurrentAmmo.pop_back();

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
	auto newAmmo = ammoRenderer->CreateAmmo();
	this->CurrentAmmo.push_back(newAmmo);

	auto x = -35.05f;
	auto y = 15 + 0.0f;
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
	btMotionState* fallMotionState = new AmmoMotionState(newAmmo, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
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

void Level::InitialiseTerrain(ExtraLargeRectangleRenderer* cubeRenderer)
{
	auto smallRect = cubeRenderer->CreateRectangle();
	m_cubes.push_back(smallRect);

	auto x = -18.0f;
	auto y = 0.0f;
	auto z = 0.0f;

	auto fallShape = new btBoxShape(btVector3(btScalar(7.50f), btScalar(8.50f), btScalar(2.50f)));
	btMotionState* fallMotionState = new CubeMotionState(smallRect, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass = 1.0f;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	m_physics.AddPhysicalObject(fallShape, fallMotionState, mass, fallInertia);
}

void Level::Initialise(PseudoSphereRenderer* sphereRenderer)
{
	/*btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	auto groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	m_physics.AddPhysicalObject(groundShape, groundMotionState, 0, btVector3(0, 0, 0));*/

	this->targetRenderer = sphereRenderer;
	auto pig1 = sphereRenderer->CreatePseudoSphere();
	Enemies.push_back(pig1);

	auto x = 25.7825f;// -18 + .05f;
	auto y = 25;///*1*/37 + 2.3001f;
	auto z = 17.621f;



	auto fallShape1 = new btSphereShape(btScalar(0.5f));
	btMotionState* fallMotionState1 = new PseudoSphereMotionState(pig1, btTransform(btQuaternion(0, 0, 0, 1), btVector3(x, y, z)));
	btScalar mass1 = 1;
	btVector3 fallInertia1(0, 0, 0);
	fallShape1->calculateLocalInertia(mass1, fallInertia1);
	m_physics.AddPhysicalObject(fallShape1, fallMotionState1, mass1, fallInertia1);
	////
	//auto pig2 = sphereRenderer->CreatePseudoSphere();
	//Enemies.push_back(pig2);

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
	/*if (this->CurrentAmmo.at(CurrentAmmo.size() - 1)->updatedTransform != nullptr){
		m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->setCenterOfMassTransform(*this->CurrentAmmo.at(CurrentAmmo.size() - 1)->updatedTransform);
		this->CurrentAmmo.at(CurrentAmmo.size() - 1)->updatedTransform = nullptr;
	}*/
	//Óïðàâëåíèå ìûøüþ
	//if (this->CurrentAmmo.at(CurrentAmmo.size() - 1)->deltaX > 0.0f ||
	//	this->CurrentAmmo.at(CurrentAmmo.size() - 1)->deltaY > 0.0f)
	//{
	//	m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->applyImpulse(btVector3(this->CurrentAmmo.at(CurrentAmmo.size() - 1)->deltaX / 100, this->CurrentAmmo.at(CurrentAmmo.size() - 1)->deltaY / 100, 0), btVector3(0.f, 1.5f, 0));

	//	this->CurrentAmmo.at(CurrentAmmo.size() - 1)->deltaX = 0.0f;
	//	this->CurrentAmmo.at(CurrentAmmo.size() - 1)->deltaY = 0.0f;
	//}
	////Óäàëåíèå óëåòåâøèõ ñíàðÿäîâ
	//auto pos = m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() - 1)->getCenterOfMassPosition();
	//
	//if (pos.getX() >= 27.0f)
	//	IsAmmoLost = true;

	////Óäàëåíèå ðàçðóøåíûõ öåëåé
	//if (m_physics.IsDestroyed && m_physics.TickCount == 0)
	//{
	//	short index = m_physics.DestroyedIndex;
	//	this->Enemies.erase(Enemies.end() + index);
	//	this->targetRenderer->Spheres.erase(targetRenderer->Spheres.end() + m_physics.DestroyedIndex);

	//	btCollisionObject* obj = m_physics.m_dynamicsWorld->getCollisionObjectArray()[m_physics.m_dynamicsWorld->getCollisionObjectArray().size() + (index - 1)];
	//	m_physics.m_dynamicsWorld->removeCollisionObject(obj);
	//	delete obj;

	//	m_physics.m_rigidBodies.at(m_physics.m_rigidBodies.size() + (index - 1)).release();
	//	m_physics.m_rigidBodies.erase(m_physics.m_rigidBodies.end() + (index - 1));
	//	m_physics.m_shapes.at(m_physics.m_shapes.size() + (index - 1)).release();
	//	m_physics.m_shapes.erase(m_physics.m_shapes.end() + (index - 1));
	//	m_physics.states.at(m_physics.states.size() + (index - 1)).release();
	//	m_physics.states.erase(m_physics.states.end() + (index - 1));

	//	m_physics.IsDestroyed = false;
	//}

	m_physics.Update();

}