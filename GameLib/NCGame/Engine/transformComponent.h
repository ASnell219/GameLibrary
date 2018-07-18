#pragma once

#include "vector2D.h"
#include "vector3D.h"
#include "matrix33.h"
#include "component.h"

class ENGINE_API TransformComponent : public Component
{
public:
	Vector2D position;
	float rotation;
	float scale;
	Matrix33 matrix;

public:
	TransformComponent(Entity* owner) : Component(owner) {}

	void Create(const Vector2D& position, float rotation = 0.0f, float scale = 1.0f);
	void Destroy();
	void Update();
};
