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
	Entity(Scene* scene, const ID& id = ID()) : m_scene(scene), Object(id) {}
	virtual ~Entity() {}

	void Update();
	void Draw();

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

protected:
	Transform m_transform;
	Scene * m_scene;
	std::vector<Component*> m_components;
};
