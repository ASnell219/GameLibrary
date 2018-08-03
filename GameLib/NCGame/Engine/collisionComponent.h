#pragma once
#include "engine.h"
#include "component.h"

class ENGINE_API ICollisionComponent : public Component
{
public:
	ICollisionComponent(Entity* owner) : Component(owner) {}

	virtual bool Intersects(ICollisionComponent* other) = 0;
};
