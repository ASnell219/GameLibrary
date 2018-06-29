#pragma once
#include "engine.h"
#include "singleton.h"
#include <map>

class AudioSystem : public Singleton<AudioSystem>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();

public:
	AudioSystem() {}
	~AudioSystem() {}

private:
	Engine * m_engine;
};