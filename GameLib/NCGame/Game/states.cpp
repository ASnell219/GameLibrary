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
	for (size_t i = 0; i < 5; i++)
	{
		Enemy* enemy = new Enemy(m_owner->GetScene());
		float x = -64.0f - (i * 32.0f);
		float y = (400.0f);
		enemy->Create(Vector2D(x, y), Vector2D(800.0f, 300.0f));
		m_owner->GetScene()->AddEntity(enemy);
	}
}

void GameState::Update()
{
}

void GameState::Exit()
{
}
