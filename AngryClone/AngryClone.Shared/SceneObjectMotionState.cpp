#include "pch.h"
#include "SceneObjectMotionState.h"


SceneObjectMotionState::SceneObjectMotionState(SceneObject^ object, const btTransform &initialTransform)
	:
	Object(object),
	m_initialTransform(initialTransform)
{

}

SceneObjectMotionState::~SceneObjectMotionState(void)
{
}

void SceneObjectMotionState::getWorldTransform(btTransform &worldTransform) const
{
	worldTransform = m_initialTransform;
}

void SceneObjectMotionState::setWorldTransform(const btTransform &worldTransform)
{
	auto rotation = worldTransform.getRotation();
	
	auto transform = ref new Transform(worldTransform.getOrigin().getX(),
		worldTransform.getOrigin().getY(),
		worldTransform.getOrigin().getZ(),
		rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW());

	Object->SetTransform(transform);
}
