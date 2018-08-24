#include "entity.h"
#include "renderComponent.h"
#include "collisionComponent.h"


void Entity::Destroy()
{
	for (Component* component : m_components)
	{
		component->Destroy();
		delete component;
	}

	m_components.clear();
}

void Entity::Update()
{
	for (Component* component : m_components)
	{
		component->Update();
	}
}

void Entity::Draw()
{
	IRenderComponent* renderComponenet = GetComponent<IRenderComponent>();
	if (renderComponenet)
	{
		renderComponenet->Draw();
	}
}

void Entity::OnEvent(const Event & event)
{
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
	(*iter)->Destroy();
	delete *iter;
	m_components.erase(iter);
	
}

bool Entity::Intersects(Entity * other)
{
	bool intersects = false;

	ICollisionComponent* collisionA = GetComponent<ICollisionComponent>();
	ICollisionComponent* collisionB = other->GetComponent<ICollisionComponent>();

	if (collisionA && collisionB)
	{
		intersects = collisionA->Intersects(collisionB);
	}

	return intersects;
}
