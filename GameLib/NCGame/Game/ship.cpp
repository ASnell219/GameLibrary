#include "ship.h"
#include "transformComponent.h"
#include "spriteComponent.h"
#include "shipControllerComponent.h"
#include "kinematicComponent.h"

void Ship::Create(const Vector2D & position)
{
	TransformComponent* transformComponent = AddComponent<TransformComponent>();
	
	transformComponent->Create(Vector2D(position));
	this->AddComponent(transformComponent);

	SpriteComponent* spriteComponent = new SpriteComponent(this);
	spriteComponent->Create("..\\content\\ship.png");
	this->AddComponent(spriteComponent);

	ShipControllerComponent* shipControllerComponent = new ShipControllerComponent(this);
	shipControllerComponent->Create(800.0f);
	this->AddComponent(shipControllerComponent);

	KinematicComponent* kinematic = new KinematicComponent(this);
	kinematic->Create(500.0f, 0.3f);
	this->AddComponent(kinematic);

}
