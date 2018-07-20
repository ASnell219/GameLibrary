#pragma once

#include "controllerComponent.h"

class ENGINE_API ShipControllerComponent : public IControllerComponent
{
public:
	ShipControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(float speed);
	void Destroy();
	void Update();

protected:
	float m_speed = 0.0f;
};