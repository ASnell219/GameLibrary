#pragma once

#include "controllerComponent.h"

class EnemyControllerComponent : public IControllerComponent
{
public:
	EnemyControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(float speed);
	void Destroy();
	void Update();

protected:
	float m_speed = 0.0f;
};