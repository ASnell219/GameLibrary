#pragma once
#include <iostream>

#include "sdl.h"

#ifdef ENGINE_EXPORTS  
#define ENGINE_API __declspec(dllexport)   
#else  
#define ENGINE_API __declspec(dllimport)   
#endif 

class ENGINE_API Engine
{
public:
	Engine() { }
	~Engine() {}

	bool Initialize();
	void Shutdown();
	void Update();

	bool IsQuit() { return m_isQuit; }
	


protected:
	bool m_isQuit = false;
	SDL_Window * m_window = nullptr;
	SDL_Renderer * m_renderer = nullptr;
};

