#pragma once

#include "entity.h"
#include "vector2D.h"

class Enemy : public Entity
{
public:
	Enemy(Scene* scene) : Entity(scene) {}
	~Enemy() {}

	void Create(const Vector2D& position);
	void Update();

};