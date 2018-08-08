#include "missile.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "timer.h"
#include "aabbComponent.h"

void Missile::Create(const ID& tag, const Vector2D & position, const Vector2D& direction, float speed)
{
	m_lifetime = 2.0f;
	SetTag(tag);
	

	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	if (tag == "playermissile") spriteComponent->Create("missile01.png", Vector2D(0.5f, 0.5f));
	else if (tag == "enemymissile") spriteComponent->Create("missile02.png", Vector2D(0.5f, 0.5f));

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.9f);
	kinematic->ApplyForce(direction * speed, KinematicComponent::VELOCITY);

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create();
}

void Missile::Update()
{
	Entity::Update();
	m_lifetime -= Timer::Instance()->DeltaTime();
	if (m_lifetime <= 0.0f)
	{
		SetState(Entity::DESTROY);
	}

}

void Missile::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "enemy" && m_tag == "playermissile")
		{
			SetState(Entity::DESTROY);
		}
	}
}