#include "pch.h"
#include "AmmoMotionState.h"

AmmoMotionState::AmmoMotionState(Ammo^ ammo, const btTransform &initialTransform) :
CurrentAmmo(ammo),
m_initialTransform(initialTransform)
{
}

AmmoMotionState::~AmmoMotionState(void)
{
}


void AmmoMotionState::getWorldTransform(btTransform &worldTransform) const
{
	worldTransform = m_initialTransform;
}

void AmmoMotionState::setWorldTransform(const btTransform &worldTransform)
{//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	auto rotation = worldTransform.getRotation();
	
	auto transform = ref new Transform(worldTransform.getOrigin().getX(),
		worldTransform.getOrigin().getY(),
		worldTransform.getOrigin().getZ(),
		rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW());

	CurrentAmmo->SetTransform(transform);
}
