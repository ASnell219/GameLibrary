#include "inputManager.h"
#include <string.h>

bool InputManager::Initialize(Engine * engine)
{
	m_engine = engine;

	SDL_GetKeyboardState(&m_numKeys);
	m_keystate = new Uint8[m_numKeys];
	m_prevKeystate = new Uint8[m_numKeys];

	const Uint8 * keystate = SDL_GetKeyboardState(nullptr);
	memcpy(m_keystate, keystate, m_numKeys);
	memcpy(m_prevKeystate, m_keystate, m_numKeys);

	for (size_t i = 0; i < 5; i++)
	{
		m_buttonState[i] = 0;
		m_prevButtonState[i] = 0;
	}

	return false;
}

void InputManager::Update()
{
	memcpy(m_prevKeystate, m_keystate, m_numKeys);
	const Uint8 * keystate = SDL_GetKeyboardState(nullptr);
	memcpy(m_keystate, keystate, m_numKeys);

	memcpy(m_prevButtonState, m_buttonState, 5);
	const Uint32 buttonState = SDL_GetMouseState(nullptr, nullptr);
	memcpy(m_buttonState, &buttonState, 5);
}

void InputManager::Shutdown()
{
	delete m_keystate;
	delete m_prevKeystate;
}

InputManager::eAction InputManager::GetButtonAction(SDL_Scancode scancode)
{
	eAction action = eAction::IDLE;

	if (m_buttonState[scancode])
	{
		action = (m_prevButtonState[scancode]) ? eAction::HELD : eAction::PRESSED;
	}
	else
	{
		action = (m_prevButtonState[scancode]) ? eAction::RELEASED : eAction::IDLE;
	}

	return action;
}

InputManager::eAction InputManager::GetMouseButtonAction(int button)
{
	eAction action = eAction::IDLE;
	button -= 1;

	if (m_keystate[button])
	{
		action = (m_prevKeystate[button]) ? eAction::HELD : eAction::PRESSED;
	}
	else
	{
		action = (m_prevKeystate[button]) ? eAction::RELEASED : eAction::IDLE;
	}


	return eAction();
}
