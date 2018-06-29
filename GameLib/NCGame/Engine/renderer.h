#pragma once
#include "engine.h"
#include "singleton.h"
#include <map>

class Renderer : public Singleton<Renderer>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();

public:
	Renderer() {}
	~Renderer() {}

private:
	Engine * m_engine;
};