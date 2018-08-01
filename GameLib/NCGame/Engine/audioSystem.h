#pragma once
#include "engine.h"
#include "singleton.h"
#include <map>
#include <fmod.hpp>

class ENGINE_API AudioSystem : public Singleton<AudioSystem>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	void AddSound(const std::string& id, const std::string& audioname);
	void PlaySound(const std::string& id, bool loop);
	void RemoveSound(const std::string& id);


	friend Singleton<AudioSystem>;
private:
	AudioSystem() {}
	~AudioSystem() {}

private:
	Engine * m_engine;
	FMOD::System* m_fmodSystem;
	std::map<std::string, FMOD::Sound*> m_sounds;
};