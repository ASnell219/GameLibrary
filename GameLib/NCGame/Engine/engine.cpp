#include "engine.h" 

bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	return true;
}

void Engine::Shutdown()
{
	SDL_Quit();
}

void Engine::Update()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		m_isQuit = true;
		break;
	}

	SDL_SetRenderDrawColor(m_renderer, 150, 0, 255, 255);
	SDL_RenderClear(m_renderer);


	//draw
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 64;
	rect.h = 64;
	SDL_SetRenderDrawColor(m_renderer, 100, 0, 255, 100);

	SDL_RenderFillRect(m_renderer, &rect);

	SDL_RenderPresent(m_renderer);
}


