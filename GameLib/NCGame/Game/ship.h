#pragma once
#include "entity.h"
#include "vector2D.h"

class Ship : public Entity
{
public:
	Ship(){}
	~Ship(){}

	void Create(const Vector2D& position);
};
