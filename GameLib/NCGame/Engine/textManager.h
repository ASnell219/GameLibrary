#pragma once

#include "engine.h"
#include "singleton.h"
#include "color.h"
#include "vector2D.h"
#include "text.h"
#include <string>
#include <vector>

class TextManager : public Singleton<TextManager>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();

	Text* CreateText(const std::string& text, const std::string& fontName, int size, const Color& color);
	void DestroyText(Text* text);

	friend Singleton<TextManager>;

protected:
	TextManager() {}

private:
	Engine * m_engine;
	std::vector<Text*> m_texts;
};
