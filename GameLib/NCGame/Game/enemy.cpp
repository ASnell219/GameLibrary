#include "enemy.h"
#include "spriteComponent.h"
#include "kinematicComponent.h"

void Enemy::Create(const Vector2D & position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("enemy01A.png", Vector2D(0.5f, 0.5f));

	//ShipControllerComponent* shipControllerComponent = AddComponent<ShipControllerComponent>();
	//shipControllerComponent->Create(800.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

}

void Enemy::Update()
{
	Entity::Update();


}

