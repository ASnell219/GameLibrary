#pragma once
#include "id.h"
#include "engine.h"
#include <list>
#include <vector>

class Entity;

class ENGINE_API Scene
{
public:
	Scene() {}
	~Scene() {}

	bool Initialize();
	void Shutdown();
	void Update();
	void Draw();

	void AddEntity(Entity* entity);
	std::list<Entity*>::iterator RemoveEntity(Entity* entity, bool destroy = true);

	Entity* FindEntity(const ID& id);
	std::vector<Entity*> GetEntityTag(const ID& tag);

protected:
	std::list<Entity*> m_entities;
};
