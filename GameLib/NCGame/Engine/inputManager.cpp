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

	m_mouseButtonState = SDL_GetMouseState(nullptr, nullptr);
	m_prevMouseButtonState = m_mouseButtonState;

	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i))
		{
			ControllerInfo controllerInfo;
			controllerInfo.controller = SDL_GameControllerOpen(i);
			memset(controllerInfo.buttonstate, 0, SDL_CONTROLLER_BUTTON_MAX);
			memset(controllerInfo.prevButtonstate, 0, SDL_CONTROLLER_BUTTON_MAX);
			memset(controllerInfo.axis, 0, SDL_CONTROLLER_AXIS_MAX);
			memset(controllerInfo.prevAxis, 0, SDL_CONTROLLER_AXIS_MAX);

			m_controllers.push_back(controllerInfo);
		}
	}

	return false;
}

void InputManager::Update()
{
	//keyboard
	memcpy(m_prevKeystate, m_keystate, m_numKeys);
	const Uint8 * keystate = SDL_GetKeyboardState(nullptr);
	memcpy(m_keystate, keystate, m_numKeys);

	//mouse
	m_prevMouseButtonState = m_mouseButtonState;
	m_mouseButtonState = SDL_GetMouseState(nullptr, nullptr);
	m_prevMousePosition = m_mousePosition;
	SDL_Point axis;
	SDL_GetMouseState(&axis.x, &axis.y);
	m_mousePosition = axis;
}

void InputManager::Shutdown()
{
	delete m_keystate;
	delete m_prevKeystate;
}

/*InputManager::eButtonState InputManager::GetButtonAction(SDL_Scancode scancode)
{
	eButtonState action = eButtonState::IDLE;

	if (m_mouseButtonState[scancode])
	{
		action = (m_prevMouseButtonState[scancode]) ? eButtonState::HELD : eButtonState::PRESSED;
	}
	else
	{
		action = (m_prevMouseButtonState[scancode]) ? eButtonState::RELEASED : eButtonState::IDLE;
	}

	return action;
}

InputManager::eButtonState InputManager::GetMouseButtonAction(int button)
{
	eButtonState action = eButtonState::IDLE;
	button -= 1;

	if (m_keystate[button])
	{
		action = (m_prevKeystate[button]) ? eButtonState::HELD : eButtonState::PRESSED;
	}
	else
	{
		action = (m_prevKeystate[button]) ? eButtonState::RELEASED : eButtonState::IDLE;
	}


	return eButtonState();
}
*/
