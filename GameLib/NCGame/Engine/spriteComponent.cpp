#include "spriteComponent.h"
#include "entity.h"
#include "renderer.h"
#include "texture.h"

void SpriteComponent::Create(const std::string & textureName, const Vector2D& origin)
{
	m_texture = new Texture();
	m_texture->Create(textureName);
	m_origin = origin;
	
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
	Transform transform = m_owner->GetTransform();
	m_texture->Draw(transform.position, m_origin, transform.scale, transform.rotation);
	//Renderer::Instance()->DrawTexture(m_texture, m_owner->GetTransform().position, m_owner->GetTransform().scale, m_owner->GetTransform().rotation);
}
