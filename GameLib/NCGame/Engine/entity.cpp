#include "entity.h"

void Entity::AddComponent(Component * component)
{
}

void Entity::RemoveComponent(Component * component)
{
	std::vector<Component*>::iterator iter = std::find(m_components.begin(), m_components.end(), component);
	if (iter != m_components.end())
	{
		delete *iter;
		m_components.erase(iter);
	}
}
