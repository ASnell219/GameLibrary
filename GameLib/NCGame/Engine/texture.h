#pragma once

#include "vector2D.h"
#include "object.h"
#include <SDL_image.h>

class Texture : public Object
{
public:
	Texture();
	~Texture();

	bool Create(const std::string& textureName);
	bool CreateFromSurface(SDL_Surface* surface);
	void Destroy();

	void Draw(const Vector2D& position, const Vector2D& origin = Vector2D::zero, const Vector2D& scale = Vector2D::one, float angle = 0);
	Vector2D GetSize() const;

	friend class Renderer;

protected:
	SDL_Texture* m_sdlTexture;
};