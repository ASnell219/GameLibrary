#include "animationComponent.h"
#include "texture.h"
#include "timer.h"
#include "spriteComponent.h"
#include "entity.h"

void AnimationComponent::Create(const std::vector<std::string>& textureNames, float rate, ePlayback playback)
{
	for (std::string textureName : textureNames)
	{
		Texture* texture = new Texture();
		texture->Create(textureName);

		m_textures.push_back(texture);
	}

	m_rate = rate;
	m_playback = playback;
}

void AnimationComponent::Update()
{
	m_timer += Timer::Instance()->DeltaTime();
	if (m_timer >= m_rate)
	{
		m_timer -= m_rate;
		m_frame += m_direction;
		if (m_frame >= m_textures.size() || m_frame < 0)
		{
			switch (m_playback)
			{
			case ePlayback::LOOP:
				m_frame = 0;
				break;
			case ePlayback::ONE_TIME:
				m_frame = (int)m_textures.size() - 1;
				break;
			case ePlayback::ONE_TIME_DESTROY:
				m_frame = (int)m_textures.size() - 1;
				m_owner->SetState(Entity::DESTROY);
				break;
			case ePlayback::PING_PONG:
				m_direction = -m_direction;
				break;
			}	
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
