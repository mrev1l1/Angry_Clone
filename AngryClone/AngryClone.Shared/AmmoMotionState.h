#pragma once
#include <btBulletDynamicsCommon.h>
#include "Ammo.h"


class AmmoMotionState : public btMotionState
{
public:
	AmmoMotionState(){};
	AmmoMotionState(Ammo^ ammo, const btTransform &initialTransform);
	virtual ~AmmoMotionState(void);

	virtual void getWorldTransform(btTransform &worldTransform) const;
	virtual void setWorldTransform(const btTransform &worldTransform);

private:
	Ammo^ CurrentAmmo;
	btTransform m_initialTransform;
};

//int AmmoMotionState::Rotation = 0;