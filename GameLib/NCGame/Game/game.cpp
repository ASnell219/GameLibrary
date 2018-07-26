#include "game.h"
#include "engine.h"
#include "inputManager.h"
#include "audioSystem.h"
#include "textManager.h"
#include "matrix22.h"
#include "renderer.h"
#include "textureManager.h"
#include "timer.h"
#include "entity.h"
#include "scene.h"
#include "ship.h"


Vector2D position(400.0f, 300.0f);
float angle(0.0f);
Text* text;

bool Game::Initialize()
{
	bool success = m_engine->Initialize();

	m_scene = new Scene();

	Ship* ship = new Ship();
	float x = (float)(rand() % 800);
	float y = (float)(rand() % 600);
	ship->Create(Vector2D(x, y));

	m_scene->AddEntity(ship);

	m_running = success;

	return success;
}

void Game::Shutdown()
{
	m_engine->Shutdown();
}

void Game::Update()
{
	m_running = !m_engine->IsQuit();
	m_engine->Update();

	m_scene->Update();

	Renderer::Instance()->BeginFrame();
	Renderer::Instance()->SetColor(Color::cyan);

	m_scene->Draw();

	Renderer::Instance()->EndFrame();
}




//InputManager::Instance()->AddAction("fire", SDL_BUTTON_LEFT, InputManager::eDevice::MOUSE);


//InputManager::Instance()->AddAction("horn", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);
//AudioSystem::Instance()->AddSound("horn", "..\\content\\horn.wav");

//text = TextManager::Instance()->CreateText("Hello!", "..\\content\\Courier.ttf", 24, Color::red);

/*onst Uint8* keystate = SDL_GetKeyboardState(nullptr);

if (InputManager::Instance()->GetActionButton("horn") == InputManager::eButtonState::PRESSED)
{
	AudioSystem::Instance()->PlaySound("horn", false);
}*/

/*SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\car.bmp");
Renderer::Instance()->DrawTexture(texture, position, angle);*/

//Vector2D force = Vector2D::zero;

//if (keystate[SDL_SCANCODE_LEFT])  angle -= 80.0f * Timer::Instance()->DeltaTime();
//if (keystate[SDL_SCANCODE_RIGHT]) angle += 80.0f * Timer::Instance()->DeltaTime();

//if (keystate[SDL_SCANCODE_UP])   force.y -= 200.0f * Timer::Instance()->DeltaTime();
//if (keystate[SDL_SCANCODE_DOWN]) force.y += 200.0f * Timer::Instance()->DeltaTime();

//Matrix22 mx;
//mx.Rotate(angle * Math::DegreesToRadians);
//force = force * mx;
//position = position + force;

//std::vector<Color> colors = { Color::red, Color::green, Color::white };
//text->SetText("Hello World!", colors[rand() % colors.size()]);
//text->Draw(Vector2D(10.0f, 10.0f), 0.0f);