#pragma once
#include "component.h"
#include "engine.h"
#include <vector>

class Texture;

class ENGINE_API AnimationComponent : public Component
{
public:
	AnimationComponent(Entity* owner) : Component(owner) {}

	void Create(const std::vector<std::string>& textureNames, float rate);
	void Update();
	void Destroy();

	Texture* GetTexture();

protected:
	std::vector<Texture*> m_textures;
	float m_rate = 0.0f;
	float m_timer = 0.0f;
	size_t m_frame = 0;
};

