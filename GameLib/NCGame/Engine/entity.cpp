#include "entity.h"
#include "renderComponent.h"


void Entity::Update()
{
	for (Component* component : m_components)
	{
		component->Update();
	}
}

void Entity::Draw()
{
	IRenderComponent* renderComponenet = GetComponenet<IRenderComponent>();
	if (renderComponenet)
	{
		renderComponenet->Draw();
	}
}

void Entity::AddComponent(Component * component)
{
	//assert(component);

	m_components.push_back(component);
}

void Entity::RemoveComponent(Component * component)
{
	//assert(std::find(m_components.begin(), m_components.end(), component) != m_components.end());
	
	auto iter = std::find(m_components.begin(), m_components.end(), component);

	delete *iter;
	m_components.erase(iter);
	
}
