#include "transformController.h"
#include "entity.h"
#include "kinematicComponent.h"
#include "timer.h"
#include "vector2D.h"

void TransformController::Create(const Vector2D & position, float rotation, float speed, float rotateRate)
{
	m_position = position;
	m_rotation = rotation;
	m_speed = speed;
	m_rotationRate = rotateRate;
}

void TransformController::Destroy()
{
}

void TransformController::Update()
{
	float dt = Timer::Instance()->DeltaTime();

	Vector2D direction = m_position - m_owner->GetTransform().position;
	m_owner->GetTransform().rotation = Math::LerpDegrees(m_owner->GetTransform().rotation, m_rotation, m_rotationRate * dt);

	Vector2D force = direction.Normalized();
	float speedMulti = Math::Clamp01(direction.Length() / 32.0f);
	KinematicComponent * kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * (m_speed * speedMulti), KinematicComponent::VELOCITY);
	}
}
