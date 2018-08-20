#pragma once
#include "controllerComponent.h"
#include "vector2D.h"
#include <vector>

class Waypoint;
class EnemyWaypoint : public IControllerComponent
{
public:
	EnemyWaypoint(Entity* owner) : IControllerComponent(owner) {}

	void Create(float speed, const std::vector<Vector2D>& points);
	void Destroy();
	void Update();

	void SetNextWaypoint();

protected:
	float m_speed = 0.0f;

	float m_timer = 0.0f;
	float m_fireRateMin = 1.0f;
	float m_fireRateMax = 3.0f;

	Waypoint* m_waypoint = nullptr;
	size_t m_waypointIndex = 0;
	std::vector<Waypoint*> m_waypoints;
};