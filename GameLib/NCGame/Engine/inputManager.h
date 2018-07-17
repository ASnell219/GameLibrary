#pragma once
#include "engine.h"
#include "singleton.h"
#include "vector2D.h"
#include <vector>
#include <map>

class ENGINE_API InputManager : public Singleton<InputManager>
{
public:
	enum eButtonState
	{
		IDLE,
		PRESSED,
		HELD,
		RELEASED
	};

	enum eDevice
	{
		KEYBOARD,
		MOUSE,
		CONTROLLER
	};

	enum eAxis
	{
		X,
		Y
	};

	struct InputInfo
	{
		int id;
		eDevice device;
		int index;
	};

	struct ControllerInfo
	{
		SDL_GameController* controller;

		Uint32 buttonstate[SDL_CONTROLLER_BUTTON_MAX];
		Uint32 prevButtonstate[SDL_CONTROLLER_BUTTON_MAX];

		float axis[SDL_CONTROLLER_AXIS_MAX];
		float prevAxis[SDL_CONTROLLER_AXIS_MAX];
	};


public:
	bool Initialize(Engine* engine);
	void Update();
	void Shutdown();

	void AddAction(const std::string& action, int id, eDevice device, int index = 0);
	eButtonState GetActionButton(const std::string& action);
	float GetActionAxisAbsolute(const std::string& action);
	float GetActionAxisRelative(const std::string& action);

	float GetAxisAbsolute(int id, eDevice device = eDevice::MOUSE, int index = 0);
	float GetAxisRelative(int id, eDevice device = eDevice::MOUSE, int index = 0);

	eButtonState GetButtonState(int id, eDevice device = eDevice::KEYBOARD, int index = 0);

protected:
	bool GetButtonDown(int id, eDevice device, int index = 0);
	bool GetPreviousButtonDown(int id, eDevice device, int index = 0);

public:
	InputManager() {}
	~InputManager() {}

private:
	Engine * m_engine;
	//keyboard
	Uint8 * m_keystate;
	Uint8 * m_prevKeystate;
	int m_numKeys;

	//mouse
	Uint8 m_mouseButtonState;
	Uint8 m_prevMouseButtonState; 
	Vector2D m_mousePosition;
	Vector2D m_prevMousePosition;

	//controller
	std::vector<ControllerInfo> m_controllers;

	std::map<std::string, InputInfo> m_actions;
	
};