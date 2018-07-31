#pragma once

#include "object.h"
#include "component.h"
#include "scene.h"
#include "transform.h"
#include <vector>
#include <assert.h>

class ENGINE_API Entity : public Object
{
public:
	enum eState
	{
		INACTIVE,
		ACTIVE,
		DESTROY
	};

public:
	Entity(Scene* scene, const ID& id = ID()) : m_scene(scene), Object(id) {}
	virtual ~Entity() {}

	virtual void Destroy();
	virtual void Update();
	virtual void Draw();

	template<typename T>
	T* AddComponent()
	{
		T* component = new T(this);
		assert(dynamic_cast<Component*>(component));
		m_components.push_back(component);

		return component;
	}

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	template <typename T>
	T*  GetComponent()
	{
		T* component = nullptr;
		for (Component* _component : m_components)
		{
			component = dynamic_cast<T*>(_component);
			if (component != nullptr) break;
		}

		return component;
	}

	Scene* GetScene() { return m_scene; }
	Transform& GetTransform() { return m_transform; }

	eState GetState() { return m_state; }
	void SetState(eState state) { m_state = state; }

protected:
	Transform m_transform;
	Scene * m_scene;
	std::vector<Component*> m_components;
	eState m_state = eState::ACTIVE;
};
