#pragma once

#include "pch.h"
#include "Physics.h"
#include "Cube.h"
#include "Ammo.h"
#include "PseudoSphere.h"
#include "CubeRenderer.h"
#include "MyRenderer.h"
#include "AmmoRenderer.h"
#include "PseudoSphereRenderer.h"
#include "SmallRectangleRenderer.h"
#include "NormallRectangleRenderer.h"
#include "LargeRectangleRenderer.h"
#include "ExtraLargeRectangleRenderer.h"

class Level
{
public:
	Level(void);
	virtual ~Level(void);

	void InitialiseTerrain(ExtraLargeRectangleRenderer* cubeRenderer);
	void Initialise(PseudoSphereRenderer* sphereRenderer);

	
//	void InitialiseNormallRectangles(SmallRectangleRenderer* normallRectanglesRenderer);
	void InitialiseCubes(MyRenderer* cubesRenderer);
	void InitialiseAmmo(MyRenderer* ammoRenderer);
	void ReinitialiseAmmo(MyRenderer* ammoRenderer);
	void deleteTarget(short targetIndex);

	void InitialiseSmallRectangles(MyRenderer* smallRectanglesRenderer);
	void InitialiseLargeRectangles(MyRenderer* largeRectanglesRenderer);
	void InitialiseNormalRectangles(MyRenderer* normalRectanglesRenderer);
	void InitialiseExtraLargeRectangles(MyRenderer* extraLargeRectanglesRenderer);
	void InitialiseBoxes(MyRenderer* renderer);
	void InitialiseVillains(MyRenderer* renderer);
	void InitialiseTerrain();

	void Update();
	
	void Kick();
	void Punch();
	void Left();
	void Right();
	void Back();

	float heightfield[64];
	bool IsAmmoLost;
	/*int objToDelete;
	int objQuantity;*/
private:
	Physics m_physics;
	std::vector<Cube^> m_cubes;
	std::vector<PseudoSphere^> Enemies;
	std::vector<Ammo^> CurrentAmmo;
	MyRenderer* targetRenderer;

	//Cube^ ObjToDelete;

	/*btIndexedMesh* indexedMesh;
	unsigned char* IndexBase;
	unsigned char* vertexBase;*/
	
};

