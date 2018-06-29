#pragma once
#include "engine.h"
#include "singleton.h"
#include <map>

class InputManager : public Singleton<InputManager>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();

public:
	InputManager() {}
	~InputManager() {}

private:
	Engine * m_engine;
};