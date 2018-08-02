#pragma once
#include "entity.h"
#include "vector2D.h"

class Ship : public Entity
{
public:
	Ship(Scene* scene) : Entity(scene) {}
	~Ship(){}

	void Create(const Vector2D& position);
	void Update();
};
