#include "states.h"
#include "entity.h"
#include "spriteComponent.h"
#include "stateMachine.h"
#include "inputManager.h"
#include "enemy.h"
#include "formation.h"
#include "timer.h"

void TitleState::Enter()
{
	Entity* entity = m_owner->GetScene()->AddEntity<Entity>("title");
	entity->GetTransform().position = Vector2D(400.0f, 300.0f);
	SpriteComponent* spriteComponent = entity->AddComponent<SpriteComponent>();
	spriteComponent->Create("galaga.png", Vector2D(0.5f, 0.5f));
	spriteComponent->SetDepth(100);

	InputManager::Instance()->AddAction("start", SDL_SCANCODE_RETURN, InputManager::eDevice::KEYBOARD);

	m_credits = 0;
}

void TitleState::Update()
{
	if (InputManager::Instance()->GetActionButton("start") == InputManager::eButtonState::PRESSED)
	{
		m_owner->SetState("enter_stage");
	}
}

void TitleState::Exit()
{
	Entity* entity = m_owner->GetScene()->FindEntity("title");
	if (entity)
	{
		entity->SetState(Entity::eState::DESTROY);
	}
}

void EnterStageState::Enter()
{
	Timer::Instance()->Reset();
	Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->FindEntity("formation"));
	if (formation == nullptr)
	{
		formation = m_owner->GetScene()->AddEntity<Formation>("formation");
		formation->Create();
	}

}

void EnterStageState::Update()
{
	Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->FindEntity("formation"));
	formation->Update();
}

void EnterStageState::Exit()
{
}

void GameState::Enter()
{

}

void GameState::Update()
{
}

void GameState::Exit()
{
}
