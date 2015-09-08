#pragma once

#include "pch.h"
#include "SceneObject.h"
#include "Physics.h"
#include "SceneObjectRenderer.h"

class Level
{
public:
	Level(void);
	virtual ~Level(void);

	void InitialiseAmmo(SceneObjectRenderer* ammoRenderer);
	void ReinitialiseAmmo(SceneObjectRenderer* ammoRenderer);

	void InitialiseSmallRectangles(SceneObjectRenderer* smallRectanglesRenderer);
	void InitialiseLargeRectangles(SceneObjectRenderer* largeRectanglesRenderer);
	void InitialiseNormalRectangles(SceneObjectRenderer* normalRectanglesRenderer);
	void InitialiseExtraLargeRectangles(SceneObjectRenderer* extraLargeRectanglesRenderer);
	void InitialiseBoxes(SceneObjectRenderer* renderer);
	void InitialiseVillains(SceneObjectRenderer* renderer);
	void InitialiseTerrain();

	void Update();
	
	void Kick();
	void Punch();
	void Left();
	void Right();
	void Back();

	bool IsAmmoLost;
private:
	Physics PhysicsSimulationEngine;
	std::vector<SceneObject^> Objects;
};

