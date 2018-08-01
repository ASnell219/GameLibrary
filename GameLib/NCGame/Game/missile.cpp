#include "missile.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"

void Missile::Create(const Vector2D & position, const Vector2D& direction, float speed)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("missile01.png", Vector2D(0.5f, 0.5f));

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.9f);
	kinematic->ApplyForce(direction * speed, KinematicComponent::VELOCITY);
}
