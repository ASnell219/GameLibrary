#include "engine.h"
#include "textureManager.h"
#include "renderer.h"
#include "inputManager.h"
#include "audioSystem.h"
#include "vector2D.h"
#include "matrix22.h"
#include "timer.h"
#include "textManager.h"
#include <cassert>
#include <iostream>
#include <SDL_ttf.h>

Vector2D position(400.0f, 300.0f);
float angle(0.0f);

Text* text;

bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	Timer::Instance()->Initialize(this);
	Renderer::Instance()->Initialize(this);
	TextureManager::Instance()->Initialize(this);
	InputManager::Instance()->Initialize(this);
	AudioSystem::Instance()->Initialize(this);
	TextManager::Instance()->Initialize(this);

	InputManager::Instance()->AddAction("fire", SDL_BUTTON_LEFT, InputManager::eDevice::MOUSE);
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("fire", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);

	InputManager::Instance()->AddAction("horn", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);
	AudioSystem::Instance()->AddSound("horn", "..\\content\\horn.wav");
	//InputManager::Instance()->AddAction("steer", InputManager::eAxis::X)

	text = TextManager::Instance()->CreateText("Hello!", "..\\content\\Courier.ttf", 24, Color::red);

	return true;
}

void Engine::Shutdown()
{
	AudioSystem::Instance()->Shutdown();
	InputManager::Instance()->Shutdown();
	TextureManager::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();
	Timer::Instance()->Shutdown();
	TextManager::Instance()->Shutdown();
	
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Engine::Update()
{
	Timer::Instance()->Update();
	Timer::Instance()->SetTimeScale(1.0f);
	InputManager::Instance()->Update();

	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		m_isQuit = true;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_isQuit = true;
		}
		break;
	}

	SDL_PumpEvents();

	int x, y;
	SDL_GetMouseState(&x, &y);

	if (InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED)
	{
		std::cout << "button\n";
	}
	
	const Uint8* keystate = SDL_GetKeyboardState(nullptr);

	float steer = InputManager::Instance()->GetActionAxisRelative("steer");
	angle -= steer * Timer::Instance()->DeltaTime();

	if (InputManager::Instance()->GetActionButton("horn") == InputManager::eButtonState::PRESSED) 
	{ 
		AudioSystem::Instance()->PlaySound("horn", false);
	}

	Vector2D force = Vector2D::zero;
	
	if (keystate[SDL_SCANCODE_LEFT])  angle -= 80.0f * Timer::Instance()->DeltaTime();
	if (keystate[SDL_SCANCODE_RIGHT]) angle += 80.0f * Timer::Instance()->DeltaTime();

	
	if (keystate[SDL_SCANCODE_UP])   force.y -= 200.0f * Timer::Instance()->DeltaTime();
	if (keystate[SDL_SCANCODE_DOWN]) force.y += 200.0f * Timer::Instance()->DeltaTime();
	

	Matrix22 mx;
	mx.Rotate(angle * Math::DegreesToRadians);
	force = force * mx;
	position = position + force;

	Renderer::Instance()->BeginFrame();
	Renderer::Instance()->SetColor(Color::black);

	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\car.bmp");
	Renderer::Instance()->DrawTexture(texture, position, angle);

	std::vector<Color> colors = { Color::red, Color::green, Color::white };
	text->SetText("Hello World!", colors[rand() % colors.size()]);
	text->Draw(Vector2D(10.0f, 10.0f), 0.0f);

	Renderer::Instance()->EndFrame();

	/*
	SDL_SetRenderDrawColor(m_renderer, 150, 0, 255, 255);
	SDL_RenderClear(m_renderer);

	//draw
	SDL_Rect rect = { x, y, 64, 64 };
	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\cat.bmp");
	
	SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);

	//SDL_RenderCopy(m_renderer, m_texture, nullptr, &rect);
	SDL_RenderCopyEx(m_renderer, texture, nullptr, &rect, 45.0, nullptr, SDL_FLIP_NONE);

	SDL_RenderPresent(m_renderer);
	*/
}


