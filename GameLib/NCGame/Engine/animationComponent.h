#pragma once
#include "component.h"
#include "engine.h"
#include <vector>

class Texture;

class ENGINE_API AnimationComponent : public Component
{
public:
	enum ePlayback
	{
		LOOP, 
		ONE_TIME,
		ONE_TIME_DESTROY,
		PING_PONG
	};

public:
	AnimationComponent(Entity* owner) : Component(owner) {}

	void Create(const std::vector<std::string>& textureNames, float rate, ePlayback playback = ePlayback::LOOP);
	void Update();
	void Destroy();

	Texture* GetTexture();

protected:
	std::vector<Texture*> m_textures;
	ePlayback m_playback = ePlayback::LOOP;
	float m_rate = 0.0f;
	float m_timer = 0.0f;
	int m_frame = 0;
	int m_direction = 1;
};

