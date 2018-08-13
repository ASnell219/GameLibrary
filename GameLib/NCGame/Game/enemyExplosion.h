#pragma once

#include "entity.h"
#include "vector2D.h"

class EnemyExplosion : public Entity
{
public:
	EnemyExplosion(Scene* scene, const ID& id) : Entity(scene, id) {}
	~EnemyExplosion() {}

	void Create(const Vector2D& position);
	void Update();

};