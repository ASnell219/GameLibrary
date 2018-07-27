#include "spriteComponent.h"
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
	Renderer::Instance()->DrawTexture(m_texture, m_owner->GetTransform().position, m_owner->GetTransform().scale, m_owner->GetTransform().rotation);
}
