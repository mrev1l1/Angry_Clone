#pragma once
#include "Content\ShaderStructures.h"
#include "Cube.h"

ref class Ammo
{
private:
	~Ammo();
internal:
	Ammo();
	void SetTransform(const Transform^ transform);
	int Rotation;
	DirectX::XMMATRIX m_modelMatrix;
	btTransform* updatedTransform;

	float deltaX;
	float deltaY;
private:
};

