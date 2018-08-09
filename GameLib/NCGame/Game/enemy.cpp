#include "enemy.h"
#include "spriteComponent.h"
#include "kinematicComponent.h"
#include "enemyControllerComponent.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "audioSystem.h"
#include "eventManager.h"

void Enemy::Create(const Vector2D & position)
{
	SetTag("enemy");

	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	EnemyControllerComponent* enemyControllerComponent = AddComponent<EnemyControllerComponent>();
	enemyControllerComponent->Create(200.0f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("enemy01A.png", Vector2D(0.5f, 0.5f));

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create();

	AudioSystem::Instance()->AddSound("explosion", "enemy-hit01.wav");
}

void Enemy::Update()
{
	Entity::Update();

	Vector2D size = Renderer::Instance()->GetSize();
	if (m_transform.position.y > size.y + 64.0f)
	{
		float x = Math::GetRandomRange(0.0f, size.x);
		float y = -100.0f;
		m_transform.position = Vector2D(x, y);
	}

}

void Enemy::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "playermissile" || event.sender->GetTag() == "player")
		{
			Event _event;
			_event.eventID = "add_score";
			EventManager::Instance()->SendGameMessage(_event);
			AudioSystem::Instance()->PlaySound("explosion", false);
			SetState(Entity::DESTROY);
		}
	}
}

