#include "enemyControllerComponent.h"
#include "entity.h"
#include "kinematicComponent.h"
#include "timer.h"
#include "missile.h"
#include "math.h"

void EnemyControllerComponent::Create(float speed)
{
	m_speed = speed;
	m_timer = Math::GetRandomRange(m_fireRateMin, m_fireRateMax);
}

void EnemyControllerComponent::Destroy()
{
}

void EnemyControllerComponent::Update()
{
	Vector2D force = Vector2D::up;

	Entity* player = m_owner->GetScene()->FindEntity("player");
	if (player)
	{
		float dx = player->GetTransform().position.x - m_owner->GetTransform().position.x;
		if (dx < -32.0f) force.x = -1.0f;
		if (dx > 32.0f) force.x = 1.0f;
 	}

	KinematicComponent * kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}

}
