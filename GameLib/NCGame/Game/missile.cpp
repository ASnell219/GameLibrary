#include "missile.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"

void Missile::Create(const Vector2D & position, const Vector2D& direction, float speed)
{
	m_transform.position = position;

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("..\\content\\missile.png");

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.9f, true);
	kinematic->ApplyForce(direction * speed, KinematicComponent::FORCE);
}
