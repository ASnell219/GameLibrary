#include "waypointComponent.h"
#include "kinematicComponent.h"
#include "waypoint.h"
#include "timer.h"
#include "debugDraw.h"

void WaypointComponent::Create(float speed, const std::vector<Vector2D>& points)
{
	m_speed = speed;
	m_timer = Math::GetRandomRange(m_fireRateMin, m_fireRateMax);

	for (Vector2D point : points)
	{
		Waypoint* waypoint = m_owner->GetScene()->AddEntity<Waypoint>();
		waypoint->Create(point, Vector2D(60.0f, 60.0f), m_owner);
		m_waypoints.push_back(waypoint);
	}

	m_waypointIndex = 0;
	m_waypoint = m_waypoints[m_waypointIndex];
}

void WaypointComponent::Destroy()
{
	for (Waypoint* waypoint : m_waypoints)
	{
		waypoint->SetState(Entity::DESTROY);
	}
}

void WaypointComponent::Update()
{
	if (m_owner->Intersects(m_waypoint))
	{
		SetNextWaypoint();
	}

	DEBUG_DRAW_LINE(m_owner->GetTransform().position, m_waypoint->GetTransform().position, Color::black)

	float dt = Timer::Instance()->DeltaTime();
	//m_timer -= dt;

	Vector2D direction = m_waypoint->GetTransform().position - m_owner->GetTransform().position;
	float rotation = (Vector2D::GetAngle(direction) * Math::RadiansToDegrees + 90.0f);
	m_owner->GetTransform().rotation = Math::LerpDegrees(m_owner->GetTransform().rotation, rotation, 4.0f * dt);

	Vector2D force = Vector2D::Rotate(Vector2D::down, m_owner->GetTransform().rotation * Math::DegreesToRadians);

	KinematicComponent * kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}

	//if (m_timer <= 0.0f)
	//{
	//	m_timer = Math::GetRandomRange(m_fireRateMin, m_fireRateMax);
	//	Missile* missile = new Missile(m_owner->GetScene());
	//	missile->Create("enemymissile", m_owner->GetTransform().position, Vector2D::up, 600.0f);
	//	m_owner->GetScene()->AddEntity(missile);
	//}
}

void WaypointComponent::SetNextWaypoint()
{
	m_waypointIndex++;
	if (m_waypointIndex < m_waypoints.size())
	{
		m_waypoint = m_waypoints[m_waypointIndex];
	}
	else
	{
		m_isComplete = true;
		m_waypointIndex = 0;
		m_waypoint = m_waypoints[m_waypointIndex];
	}
}
