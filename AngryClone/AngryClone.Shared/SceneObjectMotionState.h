#pragma once

#include <btBulletDynamicsCommon.h>
#include "SceneObject.h"

class SceneObjectMotionState : public btMotionState
{
public:
	SceneObjectMotionState(SceneObject^ object, const btTransform &initialTransform);
	virtual ~SceneObjectMotionState(void);

	virtual void getWorldTransform(btTransform &worldTransform) const;
	virtual void setWorldTransform(const btTransform &worldTransform);
private:
	SceneObject^ Object;
	btTransform m_initialTransform;
};

