#include "enemyExplosion.h"
#include "spriteComponent.h"
#include "animationComponent.h"
#include "audioSystem.h"

void EnemyExplosion::Create(const Vector2D & position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);
	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("", Vector2D(0.5f, 0.5f));
	AnimationComponent* animation = AddComponent<AnimationComponent>();
	std::vector<std::string> textureNames = {"enemy-explosion01.png", "enemy-explosion02.png", "enemy-explosion03.png", "enemy-explosion04.png", "enemy-explosion05.png" };
	animation->Create(textureNames, 1.0f / 10.0f, AnimationComponent::ePlayback::ONE_TIME_DESTROY);

	AudioSystem::Instance()->AddSound("explosion", "enemy-hit01.wav");
	AudioSystem::Instance()->PlaySound("explosion", false);
}

void EnemyExplosion::Update()
{
	Entity::Update();
}
