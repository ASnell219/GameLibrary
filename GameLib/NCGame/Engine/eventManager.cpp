#include "eventManager.h"
#include "entity.h"

bool EventManager::Initialize(Engine * engine)
{
	m_engine = engine;

	return true;
}

void EventManager::Shutdown()
{
}

void EventManager::Update()
{
}

void EventManager::SendMessage(const Event & event)
{
	event.receiver->OnEvent(event);
}
