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

	void InitialiseSmallRectangles(SmallRectangleRenderer* smallRectanglesRenderer);
	void InitialiseNormallRectangles(NormallRectangleRenderer* normallRectanglesRenderer);
	void InitialiseNormallRectangles(SmallRectangleRenderer* normallRectanglesRenderer);
	void InitialiseLargeRectangles(LargeRectangleRenderer* largeRectanglesRenderer);
	void InitialiseExtraLargeRectangles(MyRenderer* extraLargeRectanglesRenderer);
	void InitialiseCubes(MyRenderer* cubesRenderer);
	void InitialiseAmmo(AmmoRenderer* ammoRenderer);
	void ReinitialiseAmmo(AmmoRenderer* ammoRenderer);
	void deleteTarget(short targetIndex);

	void Update();
	
	void Kick();
	void Punch();
	void Left();
	void Right();
	void Back();

	float heightfield[64];
	bool IsAmmoLost;
private:
	Physics m_physics;
	std::vector<Cube^> m_cubes;
	std::vector<PseudoSphere^> Enemies;
	std::vector<Ammo^> CurrentAmmo;
	PseudoSphereRenderer* targetRenderer;

	
};

