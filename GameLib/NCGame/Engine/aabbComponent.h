#pragma once
#include "collisionComponent.h"
#include "aabb.h"

class ENGINE_API AABBComponent : public ICollisionComponent
{
public:
	AABBComponent(Entity* owner) : ICollisionComponent(owner) {}

	void Create();
	void Destroy();
	void Update();

	bool Intersects(ICollisionComponent* other);

protected:
	AABB m_aabb;
};
