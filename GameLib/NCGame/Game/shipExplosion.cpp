#include "shipExplosion.h"
#include "spriteComponent.h"
#include "animationComponent.h"
#include "audioSystem.h"

void ShipExplosion::Create(const Vector2D & position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);
	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("", Vector2D(0.5f, 0.5f));
	AnimationComponent* animation = AddComponent<AnimationComponent>();
	std::vector<std::string> textureNames = { "ship-explosion01.png", "ship-explosion02.png", "ship-explosion03.png", "ship-explosion04.png"};
	animation->Create(textureNames, 1.0f / 10.0f, AnimationComponent::ePlayback::ONE_TIME_DESTROY);

	AudioSystem::Instance()->AddSound("shipExplosion", "ship-explosion.wav");
	AudioSystem::Instance()->PlaySound("shipExplosion", false);
}

void ShipExplosion::Update()
{
	Entity::Update();
}