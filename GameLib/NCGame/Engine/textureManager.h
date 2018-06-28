#pragma once
#include "engine.h"
#include <map>

class TextureManager
{
public:
	TextureManager() {}
	~TextureManager() {}

	bool Initialize(Engine* engine);
	void Shutdown();

	SDL_Texture* GetTexture(const std::string& textureName);

private:
	Engine * m_engine;
	std::map<std::string, SDL_Texture*> m_textures;

};