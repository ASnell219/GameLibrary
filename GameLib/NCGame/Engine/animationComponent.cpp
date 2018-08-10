#include "animationComponent.h"
#include "texture.h"
#include "timer.h"
#include "spriteComponent.h"
#include "entity.h"

void AnimationComponent::Create(const std::vector<std::string>& textureNames, float rate)
{
	for (std::string textureName : textureNames)
	{
		Texture* texture = new Texture();
		texture->Create(textureName);

		m_textures.push_back(texture);
	}

	m_rate = rate;
}

void AnimationComponent::Update()
{
	m_timer += Timer::Instance()->DeltaTime();
	if (m_timer >= m_rate)
	{
		m_timer -= m_rate;
		m_frame++;
		if (m_frame >= m_textures.size())
		{
			m_frame = 0;
		}
	}

	SpriteComponent* sprite = m_owner->GetComponent<SpriteComponent>();
	if (sprite)
	{
		sprite->SetTexture(GetTexture());
	}
}

void AnimationComponent::Destroy()
{
	for (Texture* texture : m_textures)
	{
		texture->Destroy();
		delete texture;
	}
	m_textures.clear();
}

Texture * AnimationComponent::GetTexture()
{
	return m_textures[m_frame];
}
