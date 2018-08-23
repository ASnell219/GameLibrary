#pragma once
#include "controllerComponent.h"
#include "vector2D.h"

class TransformController : public IControllerComponent
{
public:
	TransformController(Entity* owner) : IControllerComponent(owner) {}

	void Create(const Vector2D& position, float rotation, float speed, float rotateRate);
	void Destroy();
	void Update();

protected:
	float m_speed = 0.0f;
	Vector2D m_position;
	float m_rotation;
	float m_rotationRate = 0.0f;
};