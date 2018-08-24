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
#include "enemyWaypoint.h"
#include "animationComponent.h"
#include "transformController.h"
#include "timer.h"

std::vector<Vector2D> Enemy::m_enterPath = { Vector2D(200.0f, 400.0f), Vector2D(300.0f, 300.0f), Vector2D(200.0f, 200.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f) };

void Enemy::Create(const Info& info)
{
	m_info = info;

	SetTag("enemy");
	m_transform.position = (m_info.side == LEFT) ? Vector2D(-64.0f, 400.0f) : Vector2D(864.0f, 400.0f);
	m_transform.scale = Vector2D(2.0f, 2.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	AnimationComponent* animation = AddComponent<AnimationComponent>();

	std::vector<std::string> animations;
	if (m_info.type == BEE) animations = { "enemy02A.png", "enemy02B.png" };
	if (m_info.type == BOSS) animations = { "enemy01A.png", "enemy01B.png" };
	animation->Create(animations, 1.0f / 4.0f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("enemy01A.png", Vector2D(0.5f, 0.5f));

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create(Vector2D(0.7f, 0.9f));

	m_stateMachine = new StateMachine(GetScene(), this);
	m_stateMachine->AddState("enter_path", new EnterPathState(m_stateMachine));
	m_stateMachine->AddState("enter_formation", new EnterFormationState(m_stateMachine));
	m_stateMachine->AddState("idle", new IdleState(m_stateMachine));
	m_stateMachine->AddState("attack", new AttackState(m_stateMachine));
	m_stateMachine->SetState("enter_path");

}

void Enemy::Update()
{
	Entity::Update();

	m_stateMachine->Update();
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

void EnterPathState::Enter()
{
	EnemyWaypoint* waypoint = m_owner->GetEntity()->AddComponent<EnemyWaypoint>();
	waypoint->Create(m_owner->GetEntity<Enemy>()->m_info.speed, Enemy::m_enterPath);
}

void EnterPathState::Update()
{
	EnemyWaypoint* waypoint = m_owner->GetEntity()->GetComponent<EnemyWaypoint>();
	if (waypoint && waypoint->isComplete())
	{
		m_owner->GetEntity()->RemoveComponent(waypoint);
		m_owner->SetState("enter_formation");
	}
}

void EnterPathState::Exit()
{
}

void EnterFormationState::Enter() 
{
	EnemyWaypoint* waypoint = m_owner->GetEntity()->AddComponent<EnemyWaypoint>();
	waypoint->Create(m_owner->GetEntity<Enemy>()->m_info.speed, std::vector<Vector2D> { m_owner->GetEntity<Enemy>()->m_info.target});
}

void EnterFormationState::Update() 
{
	EnemyWaypoint* waypoint = m_owner->GetEntity()->GetComponent<EnemyWaypoint>();
	if (waypoint && waypoint->isComplete())
	{
		m_owner->GetEntity()->RemoveComponent(waypoint);
		m_owner->SetState("idle");
	}
}

void EnterFormationState::Exit() 
{

}

void IdleState::Enter()
{
	TransformController* transform = m_owner->GetEntity()->AddComponent<TransformController>();
	transform->Create(m_owner->GetEntity<Enemy>()->m_info.target, 180.0f, m_owner->GetEntity<Enemy>()->m_info.speed, 5.0f);

	m_timer = Math::GetRandomRange(m_timeMin, m_timeMax);
}

void IdleState::Update()
{
	float dt = Timer::Instance()->DeltaTime();
	m_timer = m_timer - dt;
	if (m_timer <= 0.0f)
	{
		TransformController* transform = m_owner->GetEntity()->GetComponent<TransformController>();
		m_owner->GetEntity()->RemoveComponent(transform);
		m_owner->SetState("attack");
	}
}

void AttackState::Enter()
{
	EnemyWaypoint* waypoint = m_owner->GetEntity()->AddComponent<EnemyWaypoint>();
	waypoint->Create(m_owner->GetEntity<Enemy>()->m_info.speed, Enemy::m_enterPath);
}

void AttackState::Update()
{
	EnemyWaypoint* waypoint = m_owner->GetEntity()->GetComponent<EnemyWaypoint>();
	if (waypoint && waypoint->isComplete())
	{
		m_owner->GetEntity()->RemoveComponent(waypoint);
		m_owner->SetState("enter_formation");

	}
}

void AttackState::Exit()
{
	m_owner->GetEntity()->GetTransform().position.y = -64.0f;
}
