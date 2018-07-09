#pragma once
#include "engine.h"
#include "singleton.h"
#include <map>

class InputManager : public Singleton<InputManager>
{
public:
	enum eAction
	{
		IDLE,
		PRESSED,
		HELD,
		RELEASED
	};


public:
	bool Initialize(Engine* engine);
	void Update();
	void Shutdown();

	eAction GetButtonAction(SDL_Scancode scancode);
	eAction GetMouseButtonAction(int button);


public:
	InputManager() {}
	~InputManager() {}

private:
	Engine * m_engine;
	Uint8 * m_keystate;
	Uint8 * m_prevKeystate;
	Uint8 m_buttonState[5];
	Uint8 m_prevButtonState[5]; 

	int m_numKeys;
	
};