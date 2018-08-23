#pragma once
#include "entity.h"
#include "vector2D.h"
#include "state.h"
#include "stateMachine.h"

class Enemy : public Entity
{
public:
	Enemy(Scene* scene) : Entity(scene) {}
	~Enemy() {}

	void Create(const Vector2D& position, const Vector2D& targetPosition);
	void Update();

	void OnEvent(const Event& event);

	static std::vector<Vector2D> m_enterPath;
	Vector2D m_targetPosition;

	float m_speed = 300.0f;
protected:
	StateMachine * m_stateMachine;
	
};

class EnterPathState : public IState
{
public:

	EnterPathState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
};

class EnterFormationState : public IState
{
public:
	EnterFormationState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit();
};

class IdleState : public IState
{
public:
	IdleState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit() {}

protected:
	float m_timeMin = 2.0f;
	float m_timeMax = 4.0f;
	float m_timer = 0.0f;
};

class AttackState : public IState
{
public:
	AttackState(StateMachine* owner) : IState(owner) {}

	void Enter();
	void Update();
	void Exit() {}
};