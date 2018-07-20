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
	Vector2D scale;
	Matrix33 matrix;

public:
	TransformComponent(Entity* owner) : Component(owner) {}

	void Create(const Vector2D& position, float rotation = 0.0f, const Vector2D& scale = Vector2D::one);
	void Destroy();
	void Update();
};
