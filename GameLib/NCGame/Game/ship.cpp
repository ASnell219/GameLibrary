#include "ship.h"
#include "spriteComponent.h"
#include "shipControllerComponent.h"
#include "kinematicComponent.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "explosion.h"


void Ship::Create(const Vector2D & position)
{
	SetTag("player");

	m_transform.position = position;
	m_transform.scale = Vector2D(3.0f, 3.0f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("ship.png", Vector2D(0.5f, 0.0f));

	ShipControllerComponent* shipControllerComponent = AddComponent<ShipControllerComponent>();
	shipControllerComponent->Create(800.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create(Vector2D(0.8f, 1.0f));

}

void Ship::Update()
{
	Entity::Update();

	Vector2D size = Renderer::Instance()->GetSize();
	m_transform.position.x = Math::Clamp(m_transform.position.x, 0.0f, size.x);
}

void Ship::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "enemy" || event.sender->GetTag() == "enemymissile")
		{
			Explosion* ship = m_scene->AddEntity<Explosion>();
			ship->Create(m_transform.position, Explosion::eType::PLAYER);

			SetState(Entity::DESTROY);
		}
	}
	
}
