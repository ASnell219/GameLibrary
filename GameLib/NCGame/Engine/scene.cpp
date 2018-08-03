#include "scene.h"
#include "entity.h"
#include "collisionComponent.h"
#include <assert.h>
#include <list>

bool Scene::Initialize()
{
	return true;
}

void Scene::Shutdown()
{
	for (Entity* entity : m_entities)
	{
		delete entity;
	}
	m_entities.clear();
}

void Scene::Update()
{
	for (Entity* entity : m_entities)
	{
		entity->Update();
	}

	std::vector<ICollisionComponent*> collisionComponents;
	for (Entity* entity : m_entities)
	{
		ICollisionComponent* collisionComponent = entity->GetComponent<ICollisionComponent>();
		if (collisionComponent)
		{
			collisionComponents.push_back(collisionComponent);
		}
	}

	for (size_t i = 0; i < collisionComponents.size(); i++)
	{
		for (size_t j = i + 1; j < collisionComponents.size(); j++)
		{
			if (collisionComponents[i]->Intersects(collisionComponents[j]))
			{
				collisionComponents[i]->GetOwner()->SetState(Entity::DESTROY);
				collisionComponents[j]->GetOwner()->SetState(Entity::DESTROY);
			}
		}
	}

	std::list<Entity*>::iterator iter = m_entities.begin();
	while (iter != m_entities.end())
	{
		if ((*iter)->GetState() == Entity::DESTROY)
		{
			iter = RemoveEntity(*iter);
		}
		else
		{
			iter++;
		}
	}
}

void Scene::Draw()
{
	for (Entity* entity : m_entities)
	{
		entity->Draw();
	}
}

void Scene::AddEntity(Entity * entity)
{
	assert(std::find(m_entities.begin(), m_entities.end(), entity) == m_entities.end());
	assert(entity);

	m_entities.push_back(entity);
}

std::list<Entity*>::iterator Scene::RemoveEntity(Entity * entity, bool destroy)
{
	assert(std::find(m_entities.begin(), m_entities.end(), entity) != m_entities.end());
	assert(entity);

	auto iter = std::find(m_entities.begin(), m_entities.end(), entity);
	if (iter != m_entities.end())
	{
		if (destroy)
		{
			(*iter)->Destroy();
			delete *iter;
		}
		iter = m_entities.erase(iter);
	}

	return iter;
}

Entity * Scene::FindEntity(const ID & id)
{
	Entity* entity = nullptr;
	for (Entity* _entity : m_entities)
	{
		if (*_entity == id)
		{
			entity = _entity;
			break;
		}
	}
	return entity;
}

std::vector<Entity*> Scene::GetEntityTag(const ID & tag)
{
	std::vector<Entity*> entities;

	for (Entity* entity : m_entities)
	{
		if (entity->GetTag() == tag)
		{
			entities.push_back(entity);
		}
	}

	return entities;
}
