#pragma once

#include "object.h"
#include "component.h"
#include <vector>

class ENGINE_API Entity : public Object
{
public:
	Entity(const ID& id = ID()) : Object(id) {}
	virtual ~Entity() {}

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	template <typename T>
	T*  GetComponenet()
	{
		T* component = nullptr;
		for (Component* _component : m_components)
		{
			component = dynamic_cast<T*>(_component);
			if (component != nullptr) break;
		}

		return component;
	}

protected:
	std::vector<Component*> m_components;
};
