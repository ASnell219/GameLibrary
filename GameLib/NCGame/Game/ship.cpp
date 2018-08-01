#include "ship.h"
#include "spriteComponent.h"
#include "shipControllerComponent.h"
#include "kinematicComponent.h"

void Ship::Create(const Vector2D & position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(3.0f, 3.0f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("ship.png", Vector2D(0.5f, 0.0f));

	ShipControllerComponent* shipControllerComponent = AddComponent<ShipControllerComponent>();
	shipControllerComponent->Create(800.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

}
