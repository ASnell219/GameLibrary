#include "enemyTarget.h"
#include "entity.h"
#include "kinematicComponent.h"
#include "timer.h"
#include "missile.h"
#include "math.h"
#include "debugDraw.h"

void EnemyTarget::Create(const Vector2D & target, float speed)
{
	m_target = target;
	m_speed = speed;
}

void EnemyTarget::Destroy()
{
}

void EnemyTarget::Update()
{
	float dt = Timer::Instance()->DeltaTime();

	Vector2D direction = m_target - m_owner->GetTransform().position;
	float rotation = (Vector2D::GetAngle(direction) * Math::RadiansToDegrees + 90.0f);
	m_owner->GetTransform().rotation = Math::LerpDegrees(m_owner->GetTransform().rotation, rotation, 4.0f * dt);

	Vector2D force = Vector2D::Rotate(Vector2D::down, m_owner->GetTransform().rotation * Math::DegreesToRadians);
	//DEBUG_DRAW_LINE(m_owner->GetTransform().rotation, (m_owner->GetTransform().rotation + force * 60.0f), Color::black);
	
	KinematicComponent * kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}

	DEBUG_DRAW_CROSS(m_target, Vector2D(20.0f, 20.0f), Color::black);
}
