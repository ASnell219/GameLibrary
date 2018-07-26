#include "shipControllerComponent.h"
#include "inputManager.h"
#include "entity.h"
#include "transformComponent.h"
#include "timer.h"
#include "kinematicComponent.h"

void ShipControllerComponent::Create(float speed)
{
	m_speed = speed;
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("fire", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);
}

void ShipControllerComponent::Destroy()
{
}

void ShipControllerComponent::Update()
{
	Vector2D force = Vector2D::zero;
	if ((InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD))
	{
		force += Vector2D::left;
	}

	if ((InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD))
	{
		force += Vector2D::right;
	}

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}


	if ((InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::HELD))
	{
		//fire missile / create missile
	}

	//m_owner->GetComponent<TransformComponent>()->position += force * m_speed * Timer::Instance()->DeltaTime();
}
