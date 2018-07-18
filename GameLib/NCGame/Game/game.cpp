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
#include "transformComponent.h"
#include "spriteComponent.h"

Vector2D position(400.0f, 300.0f);
float angle(0.0f);
Text* text;
Entity* entity = nullptr;

bool Game::Initialize()
{
	bool success = m_engine->Initialize();
	InputManager::Instance()->AddAction("fire", SDL_BUTTON_LEFT, InputManager::eDevice::MOUSE);
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("fire", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);

	InputManager::Instance()->AddAction("horn", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);
	AudioSystem::Instance()->AddSound("horn", "..\\content\\horn.wav");

	text = TextManager::Instance()->CreateText("Hello!", "..\\content\\Courier.ttf", 24, Color::red);

	entity = new Entity(ID("player"));
	TransformComponent* transformComponent = new TransformComponent(entity);
	transformComponent->Create(Vector2D(30.0f, 30.0f));
	entity->AddComponent(transformComponent);

	SpriteComponent* spriteComponent = new SpriteComponent(entity);
	spriteComponent->Create("..\\content\\car.bmp");
	entity->AddComponent(spriteComponent);

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

	entity->Update();

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);

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

	entity->Draw();

	Renderer::Instance()->EndFrame();
}

//std::vector<Color> colors = { Color::red, Color::green, Color::white };
//text->SetText("Hello World!", colors[rand() % colors.size()]);
//text->Draw(Vector2D(10.0f, 10.0f), 0.0f);