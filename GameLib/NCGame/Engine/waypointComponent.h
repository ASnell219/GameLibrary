#pragma once
#include "engine.h"
#include "controllerComponent.h"
#include "vector2D.h"
#include <vector>

class Waypoint;
class ENGINE_API WaypointComponent : public IControllerComponent
{
public:
	WaypointComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(float speed, const std::vector<Vector2D>& points);
	void Destroy();
	void Update();

	void SetNextWaypoint();
	bool isComplete() { return m_isComplete; }

protected:
	bool m_isComplete = false;
	float m_speed = 0.0f;

	float m_timer = 0.0f;
	float m_fireRateMin = 1.0f;
	float m_fireRateMax = 3.0f;

	Waypoint* m_waypoint = nullptr;
	size_t m_waypointIndex = 0;
	std::vector<Waypoint*> m_waypoints;
};