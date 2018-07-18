#include "spriteComponent.h"

void SpriteComponent::Create(const std::string & textureName)
{
	
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
	//SDL_Point point = position;
	//SDL_Rect dest = { point.x, point.y, 0, 0 };
	//SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);
	//Vector2D size(dest.w, dest.h);
	//size = size * scale;
	//dest.w = static_cast<int>(size.x);
	//dest.h = static_cast<int>(size.y);

	//SDL_RenderCopyEx(m_renderer, texture, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);
}
