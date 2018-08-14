#pragma once
#include "engine.h"
#include <map>
class Scene;
class IState;

class ENGINE_API StateMachine
{
public:
	StateMachine(Scene* scene) : m_scene(scene) {}
	~StateMachine() {}

	void Update();

	void AddState(const std::string& stateName, IState* state);
	void SetState(const std::string& stateName);

	Scene* GetScene() { return m_scene; }

protected:
	Scene * m_scene = nullptr;
	IState* m_state = nullptr;
	std::map<std::string, IState*> m_states;
};