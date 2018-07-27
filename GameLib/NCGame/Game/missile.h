#pragma once
#include "entity.h"
#include "vector2D.h"

class Missile : public Entity
{
public:
	Missile(Scene* scene) : Entity(scene) {}
	~Missile() {}

	void Create(const Vector2D& position, const Vector2D& direction, float speed);
};