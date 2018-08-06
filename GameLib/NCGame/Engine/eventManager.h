#pragma once
#include "singleton.h"
#include "engine.h"
#include "event.h"

class ENGINE_API EventManager : public Singleton<EventManager>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	void SendMessage(const Event& event);

protected:
	friend Singleton<EventManager>;

protected:
	Engine * m_engine;
};
