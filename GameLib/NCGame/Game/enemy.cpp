#include "enemy.h"
#include "spriteComponent.h"
#include "kinematicComponent.h"
#include "enemyWaypoint.h"
#include "enemyControllerComponent.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "audioSystem.h"
#include "eventManager.h"
#include "enemyExplosion.h"

void Enemy::Create(const Vector2D & position)
{
	SetTag("enemy");

	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	//EnemyControllerComponent* enemyControllerComponent = AddComponent<EnemyControllerComponent>();
	//enemyControllerComponent->Create(200.0f);

	EnemyWaypoint* controller = AddComponent<EnemyWaypoint>();
	std::vector<Vector2D> points = { Vector2D(100.0f, 100.0f),  Vector2D(300.0f, 400.0f), Vector2D(200.0f, 650.0f) };
	controller->Create(200.0f, points);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("enemy01A.png", Vector2D(0.5f, 0.5f));

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create(Vector2D(0.7f, 0.9f));

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
			_event.variant[0].asInteger = 100;
			_event.variant[0].type = Variant::eType::INTEGER;
			EventManager::Instance()->SendGameMessage(_event);

			EnemyExplosion* explosion = m_scene->AddEntity<EnemyExplosion>();
			explosion->Create(m_transform.position);

			SetState(Entity::DESTROY);
		}
	}
}

