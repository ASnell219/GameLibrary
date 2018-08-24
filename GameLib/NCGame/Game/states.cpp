#include "states.h"
#include "entity.h"
#include "spriteComponent.h"
#include "stateMachine.h"
#include "inputManager.h"
#include "enemy.h"

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
		m_owner->SetState("game");
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

void GameState::Enter()
{
	std::vector<Enemy::Info> formation =
	{	{ Enemy::BEE, Enemy::LEFT, 400.0f, Vector2D(100.0f, 100.0f) }, 
		{ Enemy::BOSS, Enemy::RIGHT, 400.0f, Vector2D(700.0f, 100.0f) }, 
		{ Enemy::BEE, Enemy::LEFT, 400.0f, Vector2D(150.0f, 100.0f) }, 
		{ Enemy::BOSS, Enemy::RIGHT, 400.0f, Vector2D(650.0f, 100.0f) },
		{ Enemy::BEE, Enemy::LEFT, 400.0f, Vector2D(200.0f, 100.0f) },
		{ Enemy::BOSS, Enemy::RIGHT, 400.0f, Vector2D(600.0f, 100.0f) },
	};

	for (Enemy::Info info : formation)
	{
		Enemy* enemy = m_owner->GetScene()->AddEntity<Enemy>();
		enemy->Create(info);
	}

}

void GameState::Update()
{
}

void GameState::Exit()
{
}
