#include "spriteComponent.h"
#include "transformComponent.h"
#include "entity.h"
#include "renderer.h"
#include "texture.h"

void SpriteComponent::Create(const std::string & textureName)
{
	m_texture = new Texture();
	m_texture->Create(textureName);
	
}

void SpriteComponent::Destroy()
{
	//
}

void SpriteComponent::Update()
{
	//
}

void SpriteComponent::Draw()
{
	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
	Renderer::Instance()->DrawTexture(m_texture, transform->position, transform->scale, transform->rotation);
}
