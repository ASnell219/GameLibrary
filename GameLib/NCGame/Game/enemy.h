#pragma once
#include "entity.h"
#include "vector2D.h"
#include "state.h"
#include "stateMachine.h"

class Enemy : public Entity
{
public:
	enum eType
	{
		BEE,
		BOSS,
		BUG
	};

	enum eSide
	{
		BOTTOMLEFT,
		BOTTOMRIGHT,
		TOPLEFT,
		TOPRIGHT,
	};

	struct Info
	{
		eType type;
		eSide side;
		float speed;
		Vector2D target;
		class Formation* formation;
	};


public:
	Enemy(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Enemy() {}

	void Create(const Info& info);
	void Update();

	void OnEvent(const Event& event);

	static std::vector<Vector2D> m_enterPath;
	
	Info m_info;

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
	void Exit();
};