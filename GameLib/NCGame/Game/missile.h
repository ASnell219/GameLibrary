#pragma once
#include "entity.h"
#include "vector2D.h"

class Missile : public Entity
{
public:
	Missile() {}
	~Missile() {}

	void Create(const Vector2D& position);
};