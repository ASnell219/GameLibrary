#include "game.h"
#include "engine.h"
#include "renderer.h"
#include "scene.h"
#include "ship.h"
#include "fileSystem.h"
#include "enemy.h"
#include "spriteComponent.h"
#include "textComponent.h"
#include "eventManager.h"
#include "animationComponent.h"
#include "stateMachine.h"
#include "states.h"

bool Game::Initialize()
{
	bool success = m_engine->Initialize();
	FileSystem::Instance()->SetPathname("..\\content\\galaga\\");

	EventManager::Instance()->SetReceiver(this);

	m_scene = new Scene();
	m_state = new StateMachine(m_scene);

	m_state->AddState("title", new TitleState(m_state));
	m_state->AddState("game", new GameState(m_state));

	m_state->SetState("title");

	Entity* entity = new Entity(m_scene, "score");
	entity->GetTransform().position = Vector2D(20.0f, 15.0f);
	TextComponent* text = entity->AddComponent<TextComponent>();
	text->Create("000000", "emulogic.ttf", 18, Color::white);
	text->SetDepth(100);
	m_scene->AddEntity(entity);

	Ship* ship = new Ship(m_scene, "player");
	ship->Create(Vector2D(400, 510));
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

	Entity* scoreEntity = m_scene->FindEntity("score");
	if (scoreEntity)
	{
		TextComponent* text = scoreEntity->GetComponent<TextComponent>();
		std::string score = std::to_string(m_score);
		while (score.length() < 5) score = "0" + score;
		text->SetText(score);
	}

	m_state->Update();

	Renderer::Instance()->SetColor(Color::cyan);
	Renderer::Instance()->BeginFrame();
	
	m_scene->Update();
	m_scene->Draw();

	Renderer::Instance()->EndFrame();
}

void Game::OnEvent(const Event & event)
{
	if (event.eventID == "add_score")
	{
		m_score += event.variant[0].asInteger;
	}
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