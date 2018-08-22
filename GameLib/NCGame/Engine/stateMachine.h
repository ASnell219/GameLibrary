#pragma once
#include "engine.h"
#include <map>
class Scene;
class IState;

class ENGINE_API StateMachine
{
public:
	StateMachine(Scene* scene, class Entity* owner = nullptr) : m_scene(scene), m_entity(owner) {}
	~StateMachine() {}

	void Update();

	void AddState(const std::string& stateName, IState* state);
	void SetState(const std::string& stateName);

	Scene* GetScene() { return m_scene; }
	Entity* GetEntity() { return m_entity; }

	template<typename T>
	T* GetEntity()
	{
		return dynamic_cast<T*>(m_entity);
	}

protected:
	Scene * m_scene = nullptr;
	class Entity* m_entity = nullptr;
	IState* m_state = nullptr;
	std::map<std::string, IState*> m_states;
};